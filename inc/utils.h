#ifndef __MRTOS_UTILS__
#define __MRTOS_UTILS__
#include <inttypes.h>
#include <stddef.h>

typedef unsigned char byte_t;

inline unsigned min(unsigned a, unsigned b) {
  return (a < b) ? a : b;
}

#define ASSERT(test) while (0) { if( (test) == 0 ) { while (1) ; } }

void delay(uint16_t ms);
void* malloc(unsigned int bytes);
void free(void* ptr);
int strlen(const char* str);
#endif
