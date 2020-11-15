#include<stdint.h>
#include<immintrin.h>

#include"rdrand.h"

// Loop until a value is output

uint16_t rand_next_uint16() {
  uint16_t ret;
  while (!_rdrand16_step(&ret));
  return ret;
}

uint32_t rand_next_uint32() {
  uint32_t ret;
  while (!_rdrand32_step(&ret));
  return ret;
}

uint64_t rand_next_uint64() {
  uint64_t ret;
  while (!_rdrand64_step(&ret));
  return ret;
}

void rand_fill_buffer(uint8_t* buf, size_t size) {
  uint32_t* buf32 = (uint32_t*)buf;
  for (size_t i = 0; i < size >> 2; i++) {
    uint32_t generated = rand_next_uint32();
    buf32[i] = generated;
  }
  // Last unaligned part
  // Use bit magic to get the size of the part still not filled
  uint32_t bytescopied = (size & 0xFFFFFFFC);
  for (size_t i = 0; i < size - bytescopied; i++) {
    // Here we generate a 16-bit integer and then truncate it to 8 bits
    uint16_t generated = rand_next_uint16();
    uint8_t trunc = generated & 0xFF;
    buf[bytescopied + i] = trunc;
    // Not the most efficient method, but the easiest to understand.
  }
}

void rand_fill_buf_align32(uint32_t* buf, size_t size) {
  // Because we know that the pointer given is aligned to 32-bits,
  // We don't need all the other logic for filling in the unaligned portion.
  for (size_t i = 0; i < size / 4; i++) {
    uint32_t generated = rand_next_uint32();
    buf[i] = generated;
  }
}
