// *** WARNING: This AES implementation is NOT REVIEWED. DO NOT use it to protect anything important. ***

#ifndef X86_EXAMPLES_AESNI_H
#define X86_EXAMPLES_AESNI_H

#include<stdint.h>

struct aes128_result {
  uint8_t* data;
  size_t length;
};

/// <summary>
/// Encrypts a message using AES-128, which is Rijndael with 128-bit blocks and 128-bit keys.
/// </summary>
/// <param name="plaintext">
/// The plaintext to be encrypted.
/// </param>
/// <param name="text_size">
/// The size of the text, in bytes.
/// </param>
/// <param name="key">
/// The encryption key to use. Must be 128 bits, or 16 bytes.
/// </param>
/// <param name="iv">
/// The initial vector to use. Must be at least 64 bits, or 8 bytes.
/// </param>
/// <returns>
/// The encrypted ciphertext.
/// </returns>
struct aes128_result aes128_ctr_encrypt(uint8_t* plaintext, size_t text_size, uint8_t* key, uint8_t* iv);

/// <summary>
/// Decrypts a message using AES-128.
/// </summary>
/// <param name="ciphertext">
/// The ciphertext to decrypt.
/// </param>
/// <param name="text_size">
/// The size of the ciphertext, in bytes.
/// </param>
/// <param name="key">
/// The key used to encrypt the text.
/// </param>
/// <param name="iv">
/// The initial vector used to encrypt the text.
/// </param>
/// <returns>
/// The decrypted plaintext.
/// </returns>
struct aes128_result aes128_ctr_decrypt(uint8_t* ciphertext, size_t text_size, uint8_t* key, uint8_t* iv);

#endif