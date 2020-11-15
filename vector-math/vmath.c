#include<immintrin.h>

#include"vmath.h"

// All the code here is roughly the same. Load elements, perform operation,
// store elements. They just use different datatypes and operations.
// The int8 implementation contains the most comments, so you should read them first.

void vmath_add_i8(int8_t* a, const int8_t* b, size_t sz) {
  size_t i = 0;
  for (i = 0; i < sz; i += 16) { // i += 16 because SIMD handles 16 elements at once, m128 / int8 = 16
    // __m128i represents integers inside a 128-bit register
    __m128i mma = _mm_loadu_epi8(a + i); // _mm_loadu_epi8 gets 128 bits of memory and stores them in the __m128 register
    __m128i mmb = _mm_loadu_epi8(b + i); // You may see people use _mm_load_*. Those functions require the pointer to be aligned to 16-byte boundaries. _mm_loadu_* doesn't need this.
    __m128i mmc = _mm_add_epi8(mma, mmb); // _mm_add_epi8 interprets the 128-bit registers as 16x 8-bit integers and adds them
    _mm_storeu_si128((__m128*)(a + i), mmc); // There is no _mm_storeu_epi8, all integer instructions use _mm_storeu_si128.
  }
  // We need to handle if the array's size isn't divisible by 16
  i &= ~0xF; // Clear the last 4 bits, this has the same effect as rounding down to the nearest 16
  for (; i < sz; i++) { // Now fill in the last elements 1 by 1
    a[i] += b[i];
  }
}

void vmath_add_i16(int16_t* a, const int16_t* b, size_t sz) {
  size_t i = 0;
  for (i = 0; i < sz; i += 8) { // i += 8, 8 elements at once, m128 / int16 = 8
    __m128i mma = _mm_loadu_epi16(a + i); // Using _mm_loadu_* like before
    __m128i mmb = _mm_loadu_epi16(b + i);
    __m128i mmc = _mm_add_epi16(mma, mmb); // Note how instead of epi8, we write epi16. This is because the integers should be interpreted as int16.
    _mm_storeu_si128((__m128*)(a + i), mmc);
  }
  // Not divisible by 8 check
  i &= ~0x7; // Clear the last 4 bits, this has the same effect as rounding down to the nearest 16
  for (; i < sz; i++) { // Now fill in the last elements 1 by 1
    a[i] += b[i];
  }
}

void vmath_add_i32(int32_t* a, const int32_t* b, size_t sz) {
  size_t i = 0;
  for (i = 0; i < sz; i += 4) { // m128 / int32 = 4
    __m128i mma = _mm_loadu_epi32(a + i); // Use the *_epi32 family of functions to manipulate int32.
    __m128i mmb = _mm_loadu_epi32(b + i);
    __m128i mmc = _mm_add_epi32(mma, mmb);
    _mm_storeu_si128((__m128*)(a + i), mmc);
  }
  // Not divisible by 4 check
  i &= ~0x3;
  for (; i < sz; i++) {
    a[i] += b[i];
  }
}

void vmath_add_i64(int64_t* a, const int64_t* b, size_t sz) {
  size_t i = 0;
  for (i = 0; i < sz; i += 2) { // m128 / int64 = 2. Note how the larger numerical types get slower and slower. If you can, use a shorter type.
    __m128i mma = _mm_loadu_epi64(a + i); // You probably know the drill by now. *_epi64
    __m128i mmb = _mm_loadu_epi64(b + i);
    __m128i mmc = _mm_add_epi64(mma, mmb);
    _mm_storeu_si128((__m128*)(a + i), mmc);
  }
  // Not divisible by 2 check
  i &= ~0x1;
  for (; i < sz; i++) {
    a[i] += b[i];
  }
}

void vmath_add_f32(float* a, const float* b, size_t sz) {
  size_t i = 0;
  for (i = 0; i < sz; i += 4) { // The functions for floating-point types are slightly different
    // __m128 represents packed singles. Use __m128 instead of __m128i here.
    __m128 mma = _mm_loadu_ps(a + i); // Use *_ps functions to do math on these types.
    __m128 mmb = _mm_loadu_ps(b + i);
    __m128 mmc = _mm_add_ps(mma, mmb);
    _mm_storeu_ps(a + i, mmc); // Even _mm_storeu_* should use *_ps
  }
  // Not divisible by 4 check
  i &= ~0x3;
  for (; i < sz; i++) {
    a[i] += b[i];
  }
}

void vmath_add_f64(double* a, const double* b, size_t sz) {
  size_t i = 0;
  for (i = 0; i < sz; i += 2) { // m128 / float64 = 2.
    // __m128d for doubles.
    __m128d mma = _mm_loadu_pd(a + i); // Use *_pd functions to do math on doubles.
    __m128d mmb = _mm_loadu_pd(b + i);
    __m128d mmc = _mm_add_pd(mma, mmb);
    _mm_storeu_pd(a + i, mmc); // Same deal with _mm_storeu_*.
  }
  // Not divisible by 2 check
  i &= ~0x1;
  for (; i < sz; i++) {
    a[i] += b[i];
  }
}