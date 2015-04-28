// ePD1_CS    = PA15
// ePD1_SCK   = PB3
// ePD1_MOSI  = PB5

//initalize SPI
// spi_init()
// spi_set_baudrate(SPI_CLK_DIV_8)
// spi_set_cpol_cpha(0, 0)
// spi_set_mode(SPI_TX_ONLY)
// spi_set_endianess(SPI_MSB_FIRST)
// spi_disable_crc         (SPI1->CR1 &= ~(SPI_CRCEN))
// spi enable software NSS (SPI1->CR1 |= SPI_SSM)
// spi set master mode     (SPI1->CR1 |= SPI_MSTR)
// spi set to 8 bit frame  (SPI1->CR1 &= ~(SPI_DFF))
// spi enable nss          (SPI1->CR2 |= SPI_SSOE)

#include "drivers/gpio.h"
#include "drivers/spi.h"
#include "drivers/port_epd.h"

void epd_init() {
  gpio_init(GPIOA);
  gpio_init(GPIOB);

  // ePD1_BUSY  = PA8
  gpio_set_mode(GPIOA, 8, GPIO_INPUT_MODE);
  // ePD1_RESET = PB2
  gpio_set_mode(GPIOB, 2, GPIO_OUTPUT_MODE);
  // ePD1_D/C   = PB11
  gpio_set_mode(GPIOB, 11, GPIO_OUTPUT_MODE);
  // ePD1_PWR_ENn = PB10
  gpio_set_mode(GPIOB, 10, GPIO_OUTPUT_MODE);

  spi_init();
  spi_set_baudrate(SPI_CLK_DIV_8);
  spi_set_cpol_cpha(0, 0);
  spi_set_mode(SPI_TX_ONLY);
  spi_set_endianess(SPI_MSB_FIRST);
  // spi_disable_crc
  SPI1->CR1 &= ~(SPI_CRCEN);
  // spi enable software NSS
  SPI1->CR1 |= SPI_SSM;
  // spi set master mode
  SPI1->CR1 |= SPI_MSTR;
  // spi set to 8 bit frame
  SPI1->CR1 &= ~(SPI_DFF);
  // spi enable nss
  SPI1->CR2 |= SPI_SSOE;
}

void epd_pwr_en() {
  gpio_write(GPIOB, 10, 1);
}
