// *** WARNING: This AES implementation is NOT REVIEWED. DO NOT use it to protect anything important. ***

#include<stdlib.h>
#include<immintrin.h>
#include<string.h>

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
  // new_size is the size including padding
  size_t new_size = (text_size + 16) & (~0xF);
  uint8_t* ciphertext = malloc(new_size);
  // Encrypt all complete blocks
  uint8_t nonce[16]; // This is the IV + the counter
  memcpy(nonce, iv, 8);
  size_t i;
  for (i = 0; i < text_size; i += 16) {
    uint64_t counter = i >> 4;
    // x86 is a little-endian architecture
    // So these bytes will be stored little-endian
    ((uint64_t*)nonce)[1] = counter;
    // Now encrypt the nonce
    aes128_encrypt_block(nonce, key, ciphertext + i);
    // XOR the plaintext with the intermediate AES output
    __m128i intermediate = _mm_loadu_epi8(ciphertext + i);
    __m128i plainblock = _mm_loadu_epi8(plaintext + i);
    __m128i finalciphert = _mm_xor_si128(intermediate, plainblock);
    _mm_storeu_epi8(ciphertext + i, finalciphert);
  }
  // Now pad and process the buffer
  size_t unaligned_start = i - 16;
  memcpy(ciphertext + unaligned_start, plaintext + unaligned_start, text_size - unaligned_start);
  // Assumes PKCS#5 padding.
  //TODO: Support other kinds of padding
  memset(ciphertext + text_size, new_size - text_size, new_size - text_size);
  struct aes128_result ret;
  ret.data = ciphertext;
  ret.length = new_size;
  return ret;
}

struct aes128_result aes128_ctr_decrypt(uint8_t* ciphertext, size_t text_size, uint8_t* key, uint8_t* iv) {
  //TODO
}

void aes128_free_struct(struct aes128_result res) {
  free(res.data);
}