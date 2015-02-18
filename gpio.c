#include "gpio.h"

#define GPIOA_BASEADDR 0x50000000
#define GPIOX_BASEADDR(x) (GPIOA_BASEADDR + (0x0400 * x))

static inline uint32_t* gpiox_baseaddr(uint8_t port) {
  return (uint32_t*)(GPIOA_BASEADDR + (0x0400 * port));
}

void gpio_init(uint8_t port) {
  // Enable the GPIO timer
  *((unsigned *)(0X40021000 + 0x2C)) |= (1 << port);
}

void gpio_set_mode(uint8_t port, uint8_t pin_num, gpio_mode_t mode) {
  uint32_t modes;
  uint32_t types;

  modes = *gpiox_baseaddr(port);
  modes &= ~(3 << (pin_num * 2));
  modes |= (mode << (pin_num * 2));
  *gpiox_baseaddr(port) = modes;

  if (mode == GPIO_OUTPUT_MODE) {
    types = *(gpiox_baseaddr(port) + 1);
    types &= ~(1 << pin_num);
    *(gpiox_baseaddr(port) + 1) = types;
  }
}

void gpio_write(uint8_t port, uint8_t pin_num, uint8_t write) {
  uint32_t data;
  data = *(gpiox_baseaddr(port) + (0x18 / 4));
  if (write) {
    *(gpiox_baseaddr(port) + 0x18 / 4) = data | (1 << pin_num);
  } else {
    *(gpiox_baseaddr(port) + 0x18 / 4) = data | (1 << (pin_num + 16));

  }
}
