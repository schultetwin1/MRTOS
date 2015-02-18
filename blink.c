#include "gpio.h"
#include "nvic.h"
#include "timer.h"
#include "vector.h"
#include "vtimer.h"

void toggle_led() {
  static int toggle = 0;
  gpio_write(GPIOB, 4, toggle);
  toggle ^= 1;
}

int main() {

  gpio_init(GPIOA);
  gpio_init(GPIOB);
  
  gpio_set_mode(GPIOB, 4, GPIO_OUTPUT_MODE);
  gpio_set_mode(GPIOA, 5, GPIO_OUTPUT_MODE);
  gpio_write(GPIOB, 4, 1);
  gpio_write(GPIOA, 5, 1);

  vtimer_t toggle;
  vtimer_init();
  vtimer_add_timer(&toggle, toggle_led, 100, 0);
  while (1)
    ;
  return 0;
}
