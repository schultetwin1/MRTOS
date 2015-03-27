#include "gpio.h"
#include "nvic.h"
#include "task.h"
#include "timer.h"
#include "utils.h"
#include "vector.h"
#include "vtimer.h"

void toggle_ledA(void* args) {
  int toggle = 0;
  while (1) {
    gpio_write(GPIOA, 5, toggle);
    toggle ^= 1;
    delay(100);
    task_yield();
  }
}

void toggle_ledB(void* args) {
  int toggle = 0;
  while (1) {
    gpio_write(GPIOB, 4, toggle);
    toggle ^= 1;
    delay(100);
    task_yield();
  }
}

int main() {
  gpio_init(GPIOA);
  gpio_init(GPIOB);
  
  gpio_set_mode(GPIOA, 5, GPIO_OUTPUT_MODE);
  gpio_set_mode(GPIOB, 4, GPIO_OUTPUT_MODE);


  //vtimer_t toggleA;
  //vtimer_t toggleB;
  //vtimer_init();
  //vtimer_add_timer(&toggleA, toggle_ledA, 1, 0);
  //vtimer_add_timer(&toggleB, toggle_ledB, 2, 0);
  // vtimer_enable();


  add_task(toggle_ledA, 0);
  add_task(toggle_ledB, 0);

  run_tasks();


  // Should never hit here
  while (1);
  return 0;
}
