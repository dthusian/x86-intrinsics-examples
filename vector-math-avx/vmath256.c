#include<immintrin.h>

#include"vmath256.h"

// You should read vector-math first to get a primer on how SIMD works.

void vmath256_add_i8(int8_t* a, const int8_t* b, size_t sz) {
  size_t i = 0;
  // AVX expands most SSE instructions to use 256-bit registers. Thus, we can process double the amount.
  for (i = 0; i < sz; i += 32) { // m256 / int8 = 32
    // Use __m256 types to specify 256-bit registers.
    __m256i mma = _mm256_loadu_epi8(a + i); // All intrinsics are now _mm256_* prefixed.
    __m256i mmb = _mm256_loadu_epi8(b + i); // Your SSE instructions still work, like loadu_*
    __m256i mmc = _mm256_add_epi8(mma, mmb); // As you can probably infer, this adds the two registers, interpreting contents as int8.
    _mm256_storeu_epi8(a + i, mmc);
  }
  // Handle unaligned elements, as always.
  i &= ~0x1F;
  for (; i < sz; i++) {
    a[i] += b[i];
  }
}

void vmath256_add_i16(int16_t* a, const int16_t* b, size_t sz) {
  size_t i = 0;
  // AVX code is really similar to the SSE version. In some cases you can put 256 everywhere and it works fine.
  for (i = 0; i < sz; i += 16) { // m256 / int16 = 16
    __m256i mma = _mm256_loadu_epi16(a + i);
    __m256i mmb = _mm256_loadu_epi16(b + i);
    __m256i mmc = _mm256_add_epi16(mma, mmb);
    _mm256_storeu_epi16(a + i, mmc); // Unlike SSE, there are seperate integer storage instructions for each integer type.
  }
  // Handle unaligned elements.
  i &= ~0xF;
  for (; i < sz; i++) {
    a[i] += b[i];
  }
}

void vmath256_add_i32(int32_t* a, const int32_t* b, size_t sz) {
  size_t i = 0;
  for (i = 0; i < sz; i += 8) { // m256 / int32 = 8
    __m256i mma = _mm256_loadu_epi32(a + i);
    __m256i mmb = _mm256_loadu_epi32(b + i);
    __m256i mmc = _mm256_add_epi32(mma, mmb);
    _mm256_storeu_epi32(a + i, mmc);
  }
  i &= ~0x7;
  for (; i < sz; i++) {
    a[i] += b[i];
  }
}

void vmath256_add_i64(int64_t* a, const int64_t* b, size_t sz) {
  size_t i = 0;
  for (i = 0; i < sz; i += 4) { // m256 / int64 = 4
    __m256i mma = _mm256_loadu_epi64(a + i);
    __m256i mmb = _mm256_loadu_epi64(b + i);
    __m256i mmc = _mm256_add_epi64(mma, mmb);
    _mm256_storeu_epi64(a + i, mmc);
  }
  i &= ~0x3;
  for (; i < sz; i++) {
    a[i] += b[i];
  }
}

void vmath256_add_f32(float* a, const float* b, size_t sz) {
  size_t i = 0;
  // You can *_ps and *_pd like SSE, as well as accompanying __m256 and __m256d types.
  for (i = 0; i < sz; i += 8) {
    __m256 mma = _mm256_loadu_ps(a + i);
    __m256 mmb = _mm256_loadu_ps(b + i);
    __m256 mmc = _mm256_add_ps(mma, mmb);
    _mm256_storeu_ps(a + i, mmc);
  }
  i &= ~0x7;
  for (; i < sz; i++) {
    a[i] += b[i];
  }
}

void vmath256_add_f64(double* a, const double* b, size_t sz) {
  size_t i = 0;
  for (i = 0; i < sz; i += 4) {
    __m256d mma = _mm256_loadu_pd(a + i);
    __m256d mmb = _mm256_loadu_pd(b + i);
    __m256d mmc = _mm256_add_pd(mma, mmb);
    _mm256_storeu_pd(a + i, mmc);
  }
  i &= ~0x3;
  for (; i < sz; i++) {
    a[i] += b[i];
  }
}