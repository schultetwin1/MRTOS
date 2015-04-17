#ifndef __MRTOS_PORT_GPIO__
#define __MRTOS_PORT_GPIO__

#define GPIOH 7
#define GPIOD 3
#define GPIOC 2
#define GPIOB 1
#define GPIOA 0

typedef enum {
  GPIO_NOPULL = 0,
  GPIO_PULLUP = 1,
  GPIO_PULLDOWN = 2,
  GPIO_RESERVED = 3
} gpio_pull_t;

typedef enum {
  GPIO_AF0 = 0,
  GPIO_AF1 = 1,
  GPIO_AF2 = 2,
  GPIO_AF3 = 3,
  GPIO_AF4 = 4,
  GPIO_AF5 = 5,
  GPIO_AF6 = 6,
  GPIO_AF7 = 7
} gpio_altfunc_t;

typedef enum {
  GPIO_INPUT_MODE    = 0,
  GPIO_OUTPUT_MODE   = 1,
  GPIO_ALT_FUNC_MODE = 2,
  GPIO_ANALOG_MODE   = 3
} gpio_mode_t;

typedef enum {
  GPIO_SPEED_VERY_LOW = 0,
  GPIO_SPEED_LOW      = 1,
  GPIO_SPEED_MEDIUM   = 2,
  GPIO_SPEED_HIGH     = 3
} gpio_speed_t;

typedef enum {
  GPIO_TYPE_PUSH_PULL = 0,
  GPIO_TYPE_OPEN_DRAIN = 1
} gpio_type_t;

void gpio_set_pull(uint8_t port, uint8_t pin_num, gpio_pull_t pull);
void gpio_set_speed(uint8_t port, uint8_t pin_num, gpio_speed_t speed);
void gpio_set_alt_func(uint8_t port, uint8_t pin_num, gpio_altfunc_t altfunc);
void gpio_set_type(uint8_t port, uint8_t pin_num, gpio_type_t type);


#endif
