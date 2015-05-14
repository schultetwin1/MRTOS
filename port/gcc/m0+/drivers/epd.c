// ePD1_CS    = PA15
// ePD1_SCK   = PB3
// ePD1_MOSI  = PB5
// ePD1_BS1 is grounded, therefore 4-lines SPI

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

void epd_cmd(uint8_t cmd);
void epd_data(uint8_t data);

const unsigned char init_data[]={
  0x00,0x00,0x00,0x55,0x00,0x00,0x55,0x55,
  0x00,0x55,0x55,0x55,0x55,0x55,0x55,0x55,
  0x55,0xAA,0x55,0x55,0xAA,0xAA,0xAA,0xAA,
  0x05,0x05,0x05,0x05,0x15,0x15,0x15,0x15,
  0x01,0x01,0x01,0x01,0x00,0x00,0x00,0x00,
  0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,
  0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,
  0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,
  0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,
  0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,
  0x34,0x32,0xF1,0x74,0x14,0x00,0x00,0x00,
  0x00,0x00
};

inline void epd_cs_low() {
  gpio_write(GPIOA, 15, 0);
}

inline void epd_cs_high() {
  gpio_write(GPIOA, 15, 1);
}

inline void epd_dc_low() {
  gpio_write(GPIOB, 11, 0);
}

inline void epd_dc_high() {
  gpio_write(GPIOB, 11, 1);
}

inline void epd_set_x_range(uint8_t x_start, uint8_t x_end) {
  // Set x start and end address
  epd_cmd(0x44);
  epd_data(x_start);
  epd_data(x_end);
}

inline void epd_set_y_range(uint8_t y_start, uint8_t y_end) {
  // Set y start and end address
  epd_cmd(0x45);
  epd_data(y_start);
  epd_data(y_end);
}

inline void epd_set_init_x(uint8_t x) {
  // Set inital x and y counter (move between start and end addresses)
  epd_cmd(0x4E);
  epd_data(x);
}

inline void epd_set_init_y(uint8_t y) {
  epd_cmd(0x4F);
  epd_data(y);
}

void epd_write_lut() {
  unsigned i;
  epd_cmd(0x32);
  for (i = 0; i < 90; i++) {
    epd_data(init_data[i]);
  }
}

void epd_init() {
  gpio_init(GPIOA);
  gpio_init(GPIOB);

  // ePD1_BUSY  = PA8
  gpio_set_mode(GPIOA, 8, GPIO_INPUT_MODE);
  gpio_set_pull(GPIOA, 8, GPIO_PULLDOWN);

  // ePD1_RESET = PB2
  gpio_set_mode(GPIOB, 2, GPIO_OUTPUT_MODE);
  gpio_set_type(GPIOB, 2, GPIO_TYPE_PUSH_PULL);
  gpio_set_pull(GPIOB, 2, GPIO_PULLUP);
  gpio_write(GPIOB, 2, 1);

  // ePD1_CS = PA15
  gpio_set_mode(GPIOA, 15, GPIO_OUTPUT_MODE);
  gpio_set_type(GPIOA, 15, GPIO_TYPE_PUSH_PULL);
  gpio_set_pull(GPIOA, 15, GPIO_NOPULL);
  gpio_set_speed(GPIOA, 15, GPIO_SPEED_HIGH);

  // ePD1_D/C   = PB11
  gpio_set_mode(GPIOB, 11, GPIO_OUTPUT_MODE);

  // ePD1_PWR_ENn = PB10
  gpio_set_mode(GPIOB, 10, GPIO_OUTPUT_MODE);
  // Enables E-paper display (pulls low)
  gpio_write(GPIOB, 10, 0);

  // Set then reset control line
  epd_cs_low();
  epd_cs_high();

  // Reset device
  epd_reset();

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
  epd_cs_high();

  // Deep sleep mode disable
  epd_cmd(0x10);
  epd_data(0x00);

  // Set data entry mode (address x auto incremented and y will incrmeent)
  epd_cmd(0x11);
  epd_data(0x03);

  // Set x start and end address
  epd_set_x_range(0x00, 0x11);

  // Set y start and end address
  epd_set_y_range(0x00, 0xAB);

  // Set inital x and y counter (move between start and end addresses)
  epd_set_init_x(0x00);
  epd_set_init_y(0x00);

  // ???? Part of example
  epd_cmd(0x21);
  epd_data(0x03);

  // Set booster feedback to internal
  epd_cmd(0xF0);
  epd_data(0x1F);

  // Write to VCOM register
  epd_cmd(0x2C);
  epd_data(0xA0);

  // Select border waveform
  epd_cmd(0x3C);
  epd_data(0x63);

  epd_cmd(0x22);
  epd_data(0xC4);

  epd_write_lut();
}

uint8_t epd_busy() {
  return gpio_read(GPIOA, 8);
}

void epd_clr() {
  int i;

  // Deep sleep mode disable
  epd_cmd(0x10);
  epd_data(0x00);

  // Set data entry mode (address x auto incremented and y will incrmeent)
  epd_cmd(0x11);
  epd_data(0x03);

  // Set x start and end address
  epd_set_x_range(0x00, 0x11);

  // Set y start and end address
  epd_set_y_range(0x00, 0xAB);

  // Set init x and y
  epd_set_init_x(0);
  epd_set_init_y(0);

  epd_cmd(0x24);
  for (i = 0; i < 3096; i++) {
    epd_data(0xFF);
  }
}

void epd_draw_block(uint8_t x, uint8_t y, uint8_t w, uint8_t h, uint8_t const * data) {
  int i;

  // Deep sleep mode disable
  epd_cmd(0x10);
  epd_data(0x00);

  // Set data entry mode (address x auto incremented and y will incrmeent)
  epd_cmd(0x11);
  epd_data(0x03);

  // Set x start and end address
  epd_set_x_range(x, x + w - 1);

  // Set y start and end address
  epd_set_y_range(y, y + h - 1);

  // Set init x and y
  epd_set_init_x(x);
  epd_set_init_y(y);

  epd_cmd(0x24);
  for (i = 0; i < (w * h); i++) {
    epd_data(data[i]);
  }
}

void epd_refresh_display() {
  while (epd_busy());
  epd_cmd(0x20);
  delay(1);
}

void epd_display_img() {
  int i;
  epd_cmd(0x24);

  for (i = 0; i < 3096; i++) {
    if (i < 18) {
      epd_data(0x00);
    } else {
      epd_data(0xFF);
    }
    //epd_data(gImage_OED[i]);
  }

  epd_cmd(0x20);
  delay(1);
  while (epd_busy());
}

void epd_pwr_en() {
  gpio_write(GPIOB, 10, 1);
}

void epd_reset() {
  gpio_write(GPIOB, 2, 0);
  delay(1);
  gpio_write(GPIOB, 2, 1);
}


void epd_cmd(uint8_t cmd) {
  while (epd_busy())
    ;
  epd_cs_low();
  epd_dc_low();
  spi_write(cmd);
  epd_cs_high();
}

void epd_data(uint8_t data) {
  while (epd_busy())
    ;
  epd_cs_low();
  epd_dc_high();
  spi_write(data);
  epd_cs_high();
}

