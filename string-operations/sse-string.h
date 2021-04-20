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
char* sse_strchr(const char*, int);

/// <summary>
/// Equivalent to the C library function strstr()
/// </summary>
char* sse_strstr(const char*, const char*);

/// <summary>
/// Equivalent to the C library function strpbrk()
/// </summary>
char* sse_strpbrk(const char*, const char*);

#endif