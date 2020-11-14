#ifndef X86_EXAMPLES_RDRAND_H
#define X86_EXAMPLES_RDRAND_H

#include<stdint.h>

/// <summary>
/// Uses hardware to generate an unsigned 16-bit integer.
/// </summary>
/// <returns>
/// The generated integer.
/// </returns>
uint16_t x86rand_next_uint16();

/// <summary>
/// Uses hardware to generate an unsigned 32-bit integer.
/// </summary>
/// <returns>
/// The generated integer.
/// </returns>
uint32_t x86rand_next_uint32();

/// <summary>
/// Uses hardware to generate an unsigned 64-bit integer.
/// </summary>
/// <returns>
/// The generated integer.
/// </returns>
uint64_t x86rand_next_uint64();

/// <summary>
/// Uses hardware random number generation to fill a buffer with random byte values.
/// </summary>
/// <param name="buf">
/// A pointer to the buffer to fill.
/// </param>
/// <param name="size">
/// The size of the buffer to fill, measured IN BYTES.
/// </param>
void x86rand_fill_buffer(uint8_t* buf, size_t size);

/// <summary>
/// Uses hardware random number generation to fill a buffer with random byte values.
/// The buffer's length must be a multiple of 32 bits. If it is not, then use the
/// x86rand_fill_buffer() function instead.
/// </summary>
/// <param name="buf">
/// A pointer to the buffer to fill.
/// </param>
/// <param name="size">
/// The size of the buffer to fill, measured IN BYTES.
/// </param>
void x86rand_fill_buf_align32(uint32_t* buf, size_t size);

#endif