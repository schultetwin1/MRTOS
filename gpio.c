#include "gpio.h"

typedef volatile struct {
  // 0x00
  uint32_t GPIOx_MODER;

  // 0x04
  uint16_t _reserved1;
  uint16_t GPIOx_OTYPER;

  // 0x08
  uint32_t GPIOx_OSPEEDR;

  // 0x0C
  uint32_t GPIOx_PUPDR;

  // 0x10
  uint16_t _reserved2;
  uint16_t GPIOx_IDR;

  // 0x14
  uint16_t _reserved3;
  uint16_t GPIOx_ODR;

  // 0x18
  uint32_t GPIOx_BSRR;

  // 0x1C
  uint16_t _reserved4;
  uint16_t GPIO_LCKR;

  // 0x20
  uint32_t GPIOx_AFRL;

  // 0x24
  uint32_t GPIOx_AFRH;

  // 0x28
  uint16_t _reserved5;
  uint16_t GPIOx_BRR;

} gpio_t;

static inline gpio_t* gpiox_baseaddr(uint8_t port) {
  const uint32_t GPIO_BASEADDR = 0x50000000;
  return (gpio_t*)(GPIO_BASEADDR + (0x0400 * port));
}

void gpio_init(uint8_t port) {
  // Enable the GPIO timer
  *((unsigned *)(0X40021000 + 0x2C)) |= (1 << port);
}

void gpio_set_mode(uint8_t port, uint8_t pin_num, gpio_mode_t mode) {
  gpio_t * const gpio = gpiox_baseaddr(port);

  gpio->GPIOx_MODER &= ~(3 << (pin_num * 2));
  gpio->GPIOx_MODER |= (mode << (pin_num * 2));

  // Set to high speed for now
  // @TODO: What does this mean?
  gpio->GPIOx_OSPEEDR |= (0x3 << (pin_num * 2));

  if (mode == GPIO_OUTPUT_MODE) {
    gpio->GPIOx_OTYPER &= ~(1 << pin_num);
  }
}

void gpio_write(uint8_t port, uint8_t pin_num, uint8_t write) {
  gpio_t * const gpio = gpiox_baseaddr(port);

  gpio->GPIOx_BSRR = 1 << (pin_num + (!write * 0x10));
}

uint8_t gpio_read(uint8_t port, uint8_t pin_num) {
  gpio_t * const gpio = gpiox_baseaddr(port);
  return (gpio->GPIOx_IDR >> pin_num) & 0x1;
}
