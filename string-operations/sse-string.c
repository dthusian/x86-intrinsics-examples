#include<immintrin.h>
#include<string.h>
#include<stddef.h>

#include"sse-string.h"

// These methods assumes that it is safe to read up to 15 bytes past the end of
// a string. This might not work in all cases.

int sse_strcmp(const char* a, const char* b) {
  while (1) {
    __m128i va = _mm_loadu_si128(a);
    __m128i vb = _mm_loadu_si128(b);
    // _mm_cmpistrc gets the Cflag of the result of PCMPISTRI
    // The Cflag indicates if the strings were equal
    if (_mm_cmpistrc(va, vb, _SIDD_CMP_EQUAL_EACH | _SIDD_NEGATIVE_POLARITY)) {
      // If the strings are not equal, we need to check the index
      // _mm_cmpistri gets the index
      int idx = _mm_cmpistri(va, vb, _SIDD_CMP_EQUAL_EACH | _SIDD_NEGATIVE_POLARITY);
      if (a[idx] < b[idx]) {
        return -1;
      }
      else if (a[idx] > b[idx]) {
        return 1;
      }
      else {
        break;
      }
    }
    a += 16;
    b += 16;
  }
  return 0;
}

char* sse_strchr(const char* str, int c) {
  __m128i vc = _mm_set1_epi8(c);
  while (1) {
    __m128i vs = _mm_loadu_si128(str);
    // Use EQUAL_EACH to check whether any character in the string is equal to c.
    if (_mm_cmpistrc(vs, vc, _SIDD_CMP_EQUAL_EACH | _SIDD_NEGATIVE_POLARITY)) {
      int idx = _mm_cmpistri(vs, vc, _SIDD_CMP_EQUAL_EACH | _SIDD_NEGATIVE_POLARITY);
      return str + idx;
    }
    else if (_mm_cmpistrz(vs, vc, _SIDD_CMP_EQUAL_EACH | _SIDD_NEGATIVE_POLARITY)) {
      return NULL;
    }
    str += 16;
  }
}

