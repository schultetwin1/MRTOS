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

#include "utils.h"
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
  gpio_set_type(GPIOB, 2, GPIO_TYPE_PUSH_PULL);
  gpio_set_pull(GPIOB, 2, GPIO_PULLUP);
  gpio_write(GPIOB, 2, 1);
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

  spi_enable();
}

void epd_pwr_en() {
  gpio_write(GPIOB, 10, 1);
}

void epd_reset() {
  gpio_write(GPIOB, 2, 0);
  delay(1);
  gpio_write(GPIOB, 2, 1);
}

uint8_t epd_busy() {
  return gpio_read(GPIOA, 8);
}

void epd_cmd(uint8_t cmd) {
  while (epd_busy())
    ;
  gpio_write(GPIOB, 11, 0);
  spi_write(cmd);
}

void epd_data(uint8_t data) {
  while (epd_busy())
    ;
  gpio_write(GPIOB, 11, 1);
  spi_write(data);
}

void epd_clr() {
  // Deep sleep mode disable
  epd_cmd(0x10);
  epd_data(0x00);

  // Set data entry mode (address x auto incremented and y will incrmeent)
  epd_cmd(0x11);
  epd_data(0x03);

  // Set x start and end address
  epd_cmd(0x44);
  epd_data(0x00);
  epd_data(0x11);

  // Set y start and end address
  epd_cmd(0x45);
  epd_data(0x00);
  epd_data(0xAB);

  // Set inital x and y counter (move between start and end addresses)
  epd_cmd(0x4E);
  epd_data(0x00);
  epd_cmd(0x4F);
  epd_data(0x00);

  // Set booster feedback to internal
  epd_cmd(0xF0);
  epd_data(0x1F);

  // Write to VCOM register
  epd_cmd(0x2C);
  epd_data(0xA0);

  epd_cmd(0x3C);
  epd_data(0x63);
}
