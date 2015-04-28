#ifndef __MRTOS_SPI__
#define __MRTOS_SPI__
#include "drivers/port_spi.h"
void spi_init();
void spi_set_cpol_cpha(uint8_t cpol, uint8_t cpha);
void spi_set_baudrate(spi_baudrate_t br);
void spi_set_mode(spi_mode_t mode);
void spi_set_endianess(spi_endianess_t endianess);

void spi_enable();
void spi_disable();

void spi_write(uint8_t* data);
void spi_read(uint8_t* data);
#endif
