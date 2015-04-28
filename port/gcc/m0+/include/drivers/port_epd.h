#ifndef __MRTOS_PORT_EPD__
#define __MRTOS_PORT_EPD__
void epd_init();
void epd_pwr_en();
void epd_reset();
uint8_t epd_busy();
void epd_clr();

#endif
