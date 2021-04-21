#ifndef X86_EXAMPLES_SSE_STRING_H
#define X86_EXAMPLES_SSE_STRING_H

#include<stdint.h>

/// <summary>
/// Equivalent to the C library function strcmp()
/// </summary>
int sse_strcmp(const char*, const char*);

/// <summary>
/// Equivalent to the C library function strchr()
/// </summary>
const char* sse_strchr(const char*, int);

#endif