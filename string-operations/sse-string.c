#include<immintrin.h>
#include<string.h>

#include"sse-string.h"

// These methods assumes that malloc always aligns to 16-byte boundaries.
// This is true for x86-64.
// They might not work on stack or statically allocated strings.

int sse_strcmp(const char* a, const char* b) {
  
}

char* sse_strchr(const char* str, int c) {
  
}
