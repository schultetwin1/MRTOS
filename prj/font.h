#ifndef __MRTOSFONT__
#define __MRTOSFONT__
#include <inttypes.h>

void font_drawchar(char c, uint8_t x, uint8_t y);
void font_drawstr(const char* str);
#endif
