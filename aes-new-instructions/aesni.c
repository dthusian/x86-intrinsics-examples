// *** WARNING: This AES implementation is NOT REVIEWED. DO NOT use it to protect anything important. ***

#include<immintrin.h>

#include"aesni.h"

const uint8_t round_constants[] = {
  0x01, 0x02, 0x04, 0x08, 0x10, 0x20, 0x40, 0x80, 0x1B, 0x36
};

#define AES_RND(rc) rkey = _mm_aeskeygenassist_si128(rkey, rc); state = _mm_aesenc_si128(state, rkey)

void aes128_encrypt_block(uint8_t* block, uint8_t* key, uint8_t* out) {
  __m128i state = _mm_loadu_si128(block);
  __m128i rkey = _mm_loadu_si128(key); // Load key
  // AddRoundKey (the first time)
  state = _mm_xor_si128(state, rkey);
  
  // 9 Rounds
  // Due to technical limitations, we cannot make this a loop
  AES_RND(0x01);
  AES_RND(0x02);
  AES_RND(0x04);
  AES_RND(0x08);
  AES_RND(0x10);
  AES_RND(0x20);
  AES_RND(0x40);
  AES_RND(0x80);
  AES_RND(0x1b);
  
  // Last round!
  rkey = _mm_aeskeygenassist_si128(rkey, 0x36);
  state = _mm_aesenclast_si128(state, rkey);
  // Return the state
  _mm_storeu_si128(out, state);
}