#include "drivers/gpio.h"
#include "drivers/spi.h"

void spi_init() {
  // Enable gpios
  gpio_init(GPIOA);
  gpio_init(GPIOB);

  // Setup MOSI, MISO, SCK, and NSS pins
  // SCK (B3)
  gpio_set_mode(GPIOB, 3, GPIO_ALT_FUNC_MODE);
  gpio_set_type(GPIOB, 3, GPIO_TYPE_PUSH_PULL);
  gpio_set_pull(GPIOB, 3, GPIO_PULLDOWN);
  gpio_set_alt_func(GPIOB, 3, GPIO_AF0);

  // MISO (B4)
  gpio_set_mode(GPIOB, 4, GPIO_ALT_FUNC_MODE);
  gpio_set_alt_func(GPIOB, 4, GPIO_AF0);

  // MOSI (B5)
  gpio_set_mode(GPIOB, 5, GPIO_ALT_FUNC_MODE);
  gpio_set_type(GPIOB, 5, GPIO_TYPE_PUSH_PULL);
  gpio_set_pull(GPIOB, 5, GPIO_PULLDOWN);
  gpio_set_alt_func(GPIOB, 5, GPIO_AF0);

  // NSS (A15)
  gpio_set_mode(GPIOA, 15, GPIO_ALT_FUNC_MODE);
  gpio_set_type(GPIOA, 15, GPIO_TYPE_PUSH_PULL);
  gpio_set_pull(GPIOA, 15, GPIO_NOPULL);
  gpio_set_alt_func(GPIOA, 15, GPIO_AF0);
}

void spi_set_baudrate(spi_baudrate_t br) {
  SPI1->CR1 &= ~(0x7 << 3);
  SPI1->CR1 |= (br << 3);
}

void spi_set_cpol_cpha(uint8_t cpol, uint8_t cpha) {
  uint16_t CR = SPI1->CR1;
  if (cpol) {
    CR |= SPI_CPOL;
  } else {
    CR &= ~(SPI_CPOL);
  }

  if (cpha) {
    CR |= SPI_CPHA;
  } else {
    CR &= ~(SPI_CPHA);
  }

  SPI1->CR1 = CR;
}

void spi_set_mode(spi_mode_t mode) {
  // @TODO: // Implement the rest
  if (mode == SPI_TX_ONLY) {
    SPI1->CR1 &= ~(SPI_RXONLY) & ~(SPI_BIDIMODE);
  }
}

void spi_set_endianess(spi_endianess_t endianess) {
  if (endianess == SPI_LSB_FIRST) {
    SPI1->CR1 |= SPI_LSBFIRST;
  } else {
    SPI1->CR1 &= ~(SPI_LSBFIRST);
  }
}

void spi_enable() {
  SPI1->CR1 |= SPI_SPE;
}

void spi_disable() {
  // @TODO: Different if in recv only mode
  while (!(SPI1->SR & SPI_RXNE))
    ;
  while (!(SPI1->SR & SPI_TXE))
    ;

  while (SPI1->SR & SPI_BSY)
    ;

  SPI1->DR;

  SPI1->CR1 &= ~(SPI_SPE);
}

void spi_write(uint16_t data) {
  while (!(SPI1->SR & SPI_TXE))
    ;
  SPI1->DR = data;
}

uint16_t spi_read() {
  while (!(SPI1->SR & SPI_RXNE))
    ;
  return SPI1->DR;
}
