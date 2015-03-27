#ifndef __MRTOS_PORT_GPIO__
#define __MRTOS_PORT_GPIO__

#define GPIOH 7
#define GPIOD 3
#define GPIOC 2
#define GPIOB 1
#define GPIOA 0

typedef enum {
  GPIO_INPUT_MODE  = 0,
  GPIO_OUTPUT_MODE = 1
} gpio_mode_t;

#endif
