#include "font.h"
#include "fontsepd.h"
#include "drivers/port_epd.h"
#include "utils.h"


void font_drawchar(char c, uint8_t x, uint8_t y) {
  epd_draw_block(x, y, Font20.Height, Font20.Width, Font20.table + (Font20.Height * Font20.Width * (c - ' ')));
}

void font_drawstr(const char* str, uint8_t x) {
  uint8_t y;
  int len = strlen(str);

  y = 63 - (((len >> 2) + 1) * Font20.Width);

  while (*str) {
    font_drawchar(*str, x, y);
    str++;
    y += Font20.Width;
  }
}
