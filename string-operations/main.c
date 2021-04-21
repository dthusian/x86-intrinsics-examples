#include"sse-string.h"
#include<stdio.h>

int main() {
  const char* str = "Hello world";
  const char* ptr = sse_strchr(str, 'o');
  printf("%lld %s", ptr - str, ptr);
}