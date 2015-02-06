#include "gpio.h"

#define GPIOA_BASEADDR 0x50000000
#define GPIOX_BASEADDR(x) (GPIOA_BASEADDR + (0x0400 * x))

void gpio_init(uint8_t port) {
  // Enable the GPIO timer
  *((unsigned *)(0X40021000 + 0x2C)) |= (1 << port);
}

void gpio_set_mode(uint8_t port, uint8_t pin_num, gpio_mode_t mode) {
  uint32_t modes;
  uint32_t types;

  modes = *((uint32_t*)(GPIOX_BASEADDR(port)));
  modes &= ~(3 << (pin_num * 2));
  modes |= (mode << (pin_num * 2));
  *((uint32_t*)(GPIOX_BASEADDR(port))) = modes;

  if (mode == GPIO_OUTPUT_MODE) {
    types = *((uint32_t*)(GPIOX_BASEADDR(port) + 4));
    types &= ~(1 << pin_num);
    *((uint32_t*)(GPIOX_BASEADDR(port) + 4)) = types;
  }
}

void gpio_write(uint8_t port, uint8_t pin_num, uint8_t write) {
  uint32_t data;
  data = *((uint32_t*)(GPIOX_BASEADDR(port) + 0x18));
  if (write) {
    *((uint32_t*)(GPIOX_BASEADDR(port) + 0x18)) = data | (1 << pin_num);
  } else {
    *((uint32_t*)(GPIOX_BASEADDR(port) + 0x18)) = data | (1 << (pin_num + 16));

  }
}
