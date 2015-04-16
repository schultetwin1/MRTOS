#include "drivers/gpio.h"
#include "drivers/port_rcc.h"

typedef volatile struct {
  // 0x00
  uint32_t GPIOx_MODER;

  // 0x04
  uint16_t GPIOx_OTYPER;
  uint16_t _reserved1;

  // 0x08
  uint32_t GPIOx_OSPEEDR;

  // 0x0C
  uint32_t GPIOx_PUPDR;

  // 0x10
  uint16_t GPIOx_IDR;
  uint16_t _reserved2;

  // 0x14
  uint16_t GPIOx_ODR;
  uint16_t _reserved3;

  // 0x18
  uint32_t GPIOx_BSRR;

  // 0x1C
  uint16_t GPIO_LCKR;
  uint16_t _reserved4;

  // 0x20
  uint32_t GPIOx_AFRL;

  // 0x24
  uint32_t GPIOx_AFRH;

  // 0x28
  uint16_t GPIOx_BRR;
  uint16_t _reserved5;

} gpio_t;

static inline gpio_t* gpiox_baseaddr(uint8_t port) {
  const uint32_t GPIO_BASEADDR = 0x50000000;
  return (gpio_t*)(GPIO_BASEADDR + (0x0400 * port));
}

void gpio_init(uint8_t port) {
  // Enable the GPIO timer
  rcc_gpio_clk_enable(port);
}

void gpio_set_mode(uint8_t port, uint8_t pin_num, gpio_mode_t mode) {
  gpio_t * const gpio = gpiox_baseaddr(port);

  gpio->GPIOx_MODER &= ~(3 << (pin_num * 2));
  gpio->GPIOx_MODER |= (mode << (pin_num * 2));

  if (mode == GPIO_OUTPUT_MODE) {
    // Set to high speed for now
    // @TODO: What does this mean?
    gpio->GPIOx_OSPEEDR |= (0x3 << (pin_num * 2));
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

void gpio_set_pull(uint8_t port, uint8_t pin_num, gpio_pull_t pull) {
  gpio_t * const gpio = gpiox_baseaddr(port);
  gpio->GPIOx_PUPDR &= ~(3 << (pin_num * 2));
  gpio->GPIOx_PUPDR |= (pull << (pin_num * 2));
}

void gpio_set_alt_func(uint8_t port, uint8_t pin_num, gpio_altfunc_t altfunc) {
  gpio_t * const gpio = gpiox_baseaddr(port);
  uint32_t volatile * AFR = &(gpio->GPIOx_AFRL);
  if (pin_num > 7) {
    AFR = &(gpio->GPIOx_AFRH);
    pin_num -= 8;
  }
  *AFR &= ~(0xF << (pin_num * 4));
  *AFR |= (altfunc << (pin_num * 4));
}
