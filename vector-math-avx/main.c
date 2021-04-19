#include"vmath256.h"
#include<stdlib.h>
#include<time.h>
#include<stdio.h>

#define BUFSIZE (1024 * 1024 * 64)

int32_t data_A[BUFSIZE];
int32_t data_B[BUFSIZE];

// Another benchmark, this time for AVX2

int main() {
  printf("Clocks per second: %ld\n", (long)CLOCKS_PER_SEC);
  for (int i = 0; i < BUFSIZE; i++) {
    data_A[i] = rand();
    data_B[i] = rand();
  }
  clock_t start, end;
  start = clock();
  vmath256_add_i32(data_A, data_B, BUFSIZE);
  end = clock();
  clock_t simd_elapsed = end - start;
  start = clock();
  for (int i = 0; i < BUFSIZE; i++) {
    data_A[i] += data_B[i];
  }
  end = clock();
  clock_t scalar_elapsed = end - start;
  int32_t deopt = 0;
  for (int i = 0; i < BUFSIZE; i++) {
    deopt += data_A[i];
  }
  printf("Deoptimization Token: %d\n", deopt);
  printf("SIMD Elapsed Clocks: %ld\n", (long)simd_elapsed);
  printf("Scalar Elapsed Clocks: %ld\n", (long)scalar_elapsed);
  printf("Speedup: %f %%\n", 100 * ((double)scalar_elapsed / (double)simd_elapsed) - 100);
}