#include "gpio.h"
#include "nvic.h"
#include "task.h"
#include "timer.h"
#include "vector.h"
#include "vtimer.h"

void toggle_ledA() {
  static int toggle = 0;
  gpio_write(GPIOA, 5, toggle);
  toggle ^= 1;
}

void toggle_ledB() {
  static int toggle = 0;
  gpio_write(GPIOB, 4, toggle);
  toggle ^= 1;
}

int main() {
  gpio_init(GPIOA);
  gpio_init(GPIOB);
  
  gpio_set_mode(GPIOA, 5, GPIO_OUTPUT_MODE);
  gpio_set_mode(GPIOB, 4, GPIO_OUTPUT_MODE);


  vtimer_t toggleA;
  vtimer_t toggleB;
  vtimer_init();
  vtimer_add_timer(&toggleA, toggle_ledA, 1, 0);
  vtimer_add_timer(&toggleB, toggle_ledB, 2, 0);
  // vtimer_enable();
  while (1)
    task_yield();
    ;
  return 0;
}
