// *** WARNING: This AES implementation is NOT REVIEWED. DO NOT use it to protect anything important. ***

#include<immintrin.h>

#include"aesni.h"

const uint8_t round_constants[] = {
  0x01, 0x02, 0x04, 0x08, 0x10, 0x20, 0x40, 0x80, 0x1B, 0x36
};

void aes128_encrypt_block(uint8_t* block, uint8_t* key, uint8_t* out) {
  __m128i state = _mm_loadu_epi8(block);
  __m128i rkey = _mm_loadu_epi8(key); // Load key
  // AddRoundKey (the first time)
  state = _mm_xor_si128(state, rkey);
  for (size_t i = 0; i < 9; i++) {
    // Generate this round's key
    rkey = _mm_aeskeygenassist_si128(rkey, round_constants[i]);
    // Do the round
    state = _mm_aesenc_si128(state, rkey);
  }
  // Last round!
  rkey = _mm_aeskeygenassist_si128(rkey, round_constants[9]);
  state = _mm_aesenc_si128(state, rkey);
  // Return the state
  _mm_storeu_si128(out, state);
}

struct aes128_result aes128_ctr_encrypt(uint8_t* plaintext, size_t text_size, uint8_t* key, uint8_t* iv) {
  // Add padding
  uint8_t padded_plaintext = (text_size + 16) & (~0xF);
  
}

struct aes128_result aes128_ctr_decrypt(uint8_t* ciphertext, size_t text_size, uint8_t* key, uint8_t* iv) {
}
