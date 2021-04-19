#ifndef X86_EXAMPLES_VMATH_H
#define X86_EXAMPLES_VMATH_H

#include<stdint.h>
#include<stddef.h>

/// <summary>
/// Elementwise adds each element of array a with the corresponding element in array b, and
/// stores the result in array a. Thanks to 2's complement bit magic, these functions work with
/// both signed and unsigned integers, given a cast.
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

void vmath_add_i8 (int8_t*  a, const int8_t*  b, size_t sz);
void vmath_add_i16(int16_t* a, const int16_t* b, size_t sz);
void vmath_add_i32(int32_t* a, const int32_t* b, size_t sz);
void vmath_add_i64(int64_t* a, const int64_t* b, size_t sz);
void vmath_add_f32(float*   a, const float*   b, size_t sz);
void vmath_add_f64(double*  a, const double*  b, size_t sz);

// The reason examples aren't given for the other arithmetic operators (sub, mul, div)
// is because they're trivial to use once you know how to use add. You can literally
// swap out intrinics functions using a macro and it'll work.

#endif