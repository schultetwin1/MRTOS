#include "gpio.h"

void gpio_set_mode(uint32_t port, uint8_t pin_num, gpio_mode_t mode) {
  uint32_t modes;
  uint32_t types;

  // Enable the GPIO timer
  *((unsigned *)(0X40021000 + 0x2C)) |= 0x3;

  modes = *((uint32_t*)(port));
  modes &= ~(3 << (pin_num * 2));
  modes |= (mode << (pin_num * 2));
  *((uint32_t*)(port)) = modes;

  if (mode == GPIO_OUTPUT_MODE) {
    types = *((uint32_t*)(port + 4));
    types &= ~(1 << pin_num);
    *((uint32_t*)(port + 4)) = types;
  }
}

void gpio_write(uint32_t port, uint8_t pin_num, uint8_t write) {
  uint32_t data;
  data = *((uint32_t*)(port + 0x18));
  if (write) {
    *((uint32_t*)(port + 0x18)) = data | (1 << pin_num);
  } else {
    *((uint32_t*)(port + 0x18)) = data | (1 << (pin_num + 16));

  }
}
