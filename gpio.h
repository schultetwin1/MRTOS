#ifndef __STM32L0_GPIO__
#define __STM32L0_GPIO__

#include <inttypes.h>

#define GPIOH 0x50001C00
#define GPIOD 0x50000C00
#define GPIOC 0x50000800
#define GPIOB 0x50000400
#define GPIOA 0x50000000

typedef enum {
  GPIO_INPUT_MODE  = 0,
  GPIO_OUTPUT_MODE = 1,
  GPIO_ALT_MODE    = 2,
  GPIO_ANALOG_MODE = 3
} gpio_mode_t;


void gpio_set_mode(uint32_t port, uint8_t pin_num, gpio_mode_t mode);
void gpio_write(uint32_t port, uint8_t pin_num, uint8_t write);
#endif
