#ifndef X86_EXAMPLES_VMATH256_H
#define X86_EXAMPLES_VMATH256_H

#include<stdint.h>
#include<stddef.h>

/// <summary>
/// Elementwise adds each element of array a with the corresponding element in array b, and
/// stores the result in array a.
/// 
/// This time around, we're using AVX, which should make the operations go even faster.
/// </summary>
/// <param name="a">
/// Operand a of the add operation. The result will be stored in this array.
/// </param>
/// <param name="b">
/// Operand b of the add operation. This array is not written to.
/// </param>
/// <param name="sz">
/// The size of both arrays, IN ELEMENTS, not bytes.
/// </param>

void vmath256_add_i8 (int8_t*  a, const int8_t*  b, size_t sz);
void vmath256_add_i16(int16_t* a, const int16_t* b, size_t sz);
void vmath256_add_i32(int32_t* a, const int32_t* b, size_t sz);
void vmath256_add_i64(int64_t* a, const int64_t* b, size_t sz);
void vmath256_add_f32(float*   a, const float*   b, size_t sz);
void vmath256_add_f64(double*  a, const double*  b, size_t sz);

#endif