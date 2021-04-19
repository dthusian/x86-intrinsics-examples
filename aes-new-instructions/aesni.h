// *** WARNING: This AES implementation is NOT REVIEWED. DO NOT use it to protect anything important. ***

#ifndef X86_EXAMPLES_AESNI_H
#define X86_EXAMPLES_AESNI_H

#include<stdint.h>
void aes128_encrypt_block(uint8_t* block, uint8_t* key, uint8_t* out);

/// <summary>
/// Frees the memory held by a aes128_result struct.
/// This should always be done on an aes128_result before it goes out of scope.
/// </summary>
/// <param name="res">
/// The aes128_result struct to be freed.
/// </param>
void aes128_free_struct(struct aes128_result res);

#endif