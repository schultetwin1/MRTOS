#ifndef __STM32L0_GPIO__
#define __STM32L0_GPIO__

#include <inttypes.h>

#define GPIOH 7
#define GPIOD 3
#define GPIOC 2
#define GPIOB 1
#define GPIOA 0


typedef enum {
  GPIO_INPUT_MODE  = 0,
  GPIO_OUTPUT_MODE = 1,
  GPIO_ALT_MODE    = 2,
  GPIO_ANALOG_MODE = 3
} gpio_mode_t;

void gpio_init(uint8_t port);
void gpio_set_mode(uint8_t port, uint8_t pin_num, gpio_mode_t mode);
void gpio_write(uint8_t port, uint8_t pin_num, uint8_t write);
uint8_t gpio_read(uint8_t port, uint8_t pin_num);
#endif
