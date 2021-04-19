// *** WARNING: This AES implementation is NOT REVIEWED. DO NOT use it to protect anything important. ***

#ifndef X86_EXAMPLES_AESNI_H
#define X86_EXAMPLES_AESNI_H

#include<stdint.h>
void aes128_encrypt_block(uint8_t* block, uint8_t* key, uint8_t* out);

#endif