#ifndef __MRTOS_UTILS__
#define __MRTOS_UTILS__
#include <inttypes.h>
#include <stddef.h>

void delay(uint16_t ms);
void* malloc(unsigned int bytes);
void free(void* ptr);
int strlen(const char* str);
#endif
