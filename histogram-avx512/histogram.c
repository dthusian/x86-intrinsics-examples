#include<immintrin.h>
#include<string.h>

#include"histogram.h"

int32_t* histogram_i32(int32_t* data, int32_t bucketsize, int32_t nbuckets, size_t sz) {
  size_t i = 0;
  __m512d g0 = _mm512_set1_pd(bucketsize);
  int32_t* histogram = malloc(nbuckets * sizeof(int32_t));
  if (histogram == NULL) return NULL;
  memset(histogram, 0, nbuckets * sizeof(int32_t));
  for (; i < (sz & ~0x3F); i++) {
    // Because int-div instructions only come with SVML, we have to make do
    // with what we have.
    // These first lines load the data and divide it
    __m256i t0 = _mm256_loadu_si256(data);
    __m512d t1 = _mm512_cvtepi32_pd(t0);
    __m512d t2 = _mm512_div_round_pd(t1, g0, _MM_FROUND_TO_ZERO | _MM_FROUND_NO_EXC);
    __m256i t3 = _mm512_cvtpd_epi32(t2);
    // At this point, t3 contains the bucket ID of each data point
    // The bucket ID is the index of the histogram memory that should be
    // incremented.

    // The naive approach is to just gather-increment-scatter, but that doesn't
    // work if there are duplicate bucket IDs, because then that entry is
    // only increased once even though many matching data points.

    /*
    You can visualize the problem with this example:

    Bucket IDs:                   { 1, 2, 3, 5, 1, 1, 4, 0 }
    Histogram data:               { 0, 0, 2, 3, 0, 1 }
    Gather is a vectorized array access
    Gathered histogram:           { 0, 2, 3, 1, 0, 0, 0, 0 }
    Incremented histogram:        { 1, 3, 4, 2, 1, 1, 1, 1 }
    Scatter is a vectorized array write
    Histogram after scattering:   { 1, 1, 3, 4, 1, 2 }

    Notice how the histogram at index 1 is only 1 even though there were
    multiple data pnts that would fall into bucket 1.
    */

    // That's where the AVX-512-CD instruction set comes in.
    // Included in the set is the instructions VPCONFLICTD and VPCONFLICTQ,
    // (and their corresponding intrinsics _mm*_conflict_epi*)

    // What these instructions do is basically an in-vector equality check with
    // every other element in the vector.

    /*
    Here we illustrate the operation of VPCONFLICTD/Q

    Vector: { 2, 3, 1, 4, 2, 5, 0, 3 }

        2 3 1 4 2 5 0 3
      +----------------
    2 | 1 0 0 0 1 0 0 0
    3 | 0 1 0 0 0 0 0 1
    1 | 0 0 1 0 0 0 0 0
    4 | 0 0 0 1 0 0 0 0
    2 | 1 0 0 0 1 0 0 0
    5 | 0 0 0 0 0 1 0 0
    0 | 0 0 0 0 0 0 1 0
    3 | 0 1 0 0 0 0 0 1
    
    Now this bit matrix is flattened and put into each corresponding element of
    the return value.

    Return vector: i32 x 8: 10001000 01000001 00100000 00010000 10001000 00000100 00000010 01000001
    
    Notice how the popcount of each element tells you if there's a conflict:
    popcount of 1 means that there's no conflict,
    popcount of above 1 means that there is.

    Also notice how instead of incrementing each gathered histogram value, we 
    can instead increase it by its conflict popcount, since that tells you how
    many of that value were in the vector.

    That principle is exactly what the below code does.
    */
    __m256i t4 = _mm256_conflict_epi32(t3);
    __m256i t5 = _mm256_i32gather_epi32(histogram, t3, 4);
    __m256i t6 = _mm256_add_epi32(t5, _mm256_popcnt_epi32(t5));
    _mm256_i32scatter_epi32(histogram, t3, t6, 4);
  }
  for (; i < sz; i++) {
    histogram[data[i] / bucketsize]++;
  }
  return histogram;
}
