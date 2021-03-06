#ifndef __MRTOS_GPIO__
#define __MRTOS_GPIO__

#include <inttypes.h>

#include "drivers/port_gpio.h"

void gpio_init(uint8_t port);
void gpio_set_mode(uint8_t port, uint8_t pin_num, gpio_mode_t mode);
void gpio_write(uint8_t port, uint8_t pin_num, uint8_t write);
uint8_t gpio_read(uint8_t port, uint8_t pin_num);
#endif
