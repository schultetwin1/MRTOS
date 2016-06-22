#ifndef __MRTOS_UTILS__
#define __MRTOS_UTILS__
#include <inttypes.h>
#include <stddef.h>

typedef unsigned char byte_t;

#define min(a,b) \
  ({ __typeof__ (a) _a = (a); \
     __typeof__ (b) _b = (b); \
     _a < _b ? _a : _b; })

#define max(a,b) \
  ({ __typeof__ (a) _a = (a); \
     __typeof__ (b) _b = (b); \
     _a > _b ? _a : _b; })

#define ASSERT(test) while (0) { if( (test) == 0 ) { while (1) ; } }

void delay(uint16_t ms);
void* malloc(unsigned int bytes);
void free(void* ptr);
int strlen(const char* str);
#endif
