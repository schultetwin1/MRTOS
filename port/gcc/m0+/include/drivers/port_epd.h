#ifndef __MRTOS_PORT_EPD__
#define __MRTOS_PORT_EPD__
void epd_init();
void epd_reset();
void epd_display_img();
void epd_draw_block(uint8_t x, uint8_t y, uint8_t w, uint8_t h, uint8_t const * data);
void epd_clr();
void epd_refresh_display();

#endif
