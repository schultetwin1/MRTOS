#include "gpio.h"
#include "timer.h"

int main() {
  uint16_t count;

  gpio_init(GPIOA);
  gpio_init(GPIOB);

  timer_init();

  gpio_set_mode(GPIOB, 4, GPIO_OUTPUT_MODE);
  gpio_set_mode(GPIOA, 5, GPIO_OUTPUT_MODE);
  gpio_write(GPIOB, 4, 1);
  gpio_write(GPIOA, 5, 1);
  while (1) {
    count = timer_count();
    count = count;
  }
}
