#include<stdio.h>
#include<stdlib.h>

#include"rdrand.h"

// Main function provides a brief demo
int main() {
  // 256-bit nonces are useful for a variety of things
  const size_t nonce_size = 256 / 8;
  uint8_t* nonce = malloc(nonce_size); 
  rand_fill_buf_align32(nonce, nonce_size);
  printf("Generating a 256-bit nonce with x86 intrinsics:\n");
  printf("hex: ");
  for (int i = 0; i < nonce_size; i++) {
    // Convert to hex and print
    uint8_t upper = nonce[i] >> 4;
    uint8_t lower = nonce[i] & 0xF;
    const char* hexlookup = "0123456789abcdef";
    putchar(hexlookup[lower]);
    putchar(hexlookup[upper]);
  }
  printf("\n");
  free(nonce);
  return 0;
}