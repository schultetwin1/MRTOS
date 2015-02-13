#include "gpio.h"
#include "nvic.h"
#include "timer.h"
#include "vector.h"

const IRQn_t TIMER_IRQn = 20;

void  __attribute__ ((interrupt ("IRQ"))) timer_handler() {
  static uint32_t toggle = 0;
  gpio_write(GPIOB, 4, toggle);
  toggle ^= 0x1;
  NVIC_ClearPendingIRQ(TIMER_IRQn);
}

int main() {
  uint16_t count;

  gpio_init(GPIOA);
  gpio_init(GPIOB);
  
  gpio_set_mode(GPIOB, 4, GPIO_OUTPUT_MODE);
  gpio_set_mode(GPIOA, 5, GPIO_OUTPUT_MODE);
  gpio_write(GPIOB, 4, 1);
  gpio_write(GPIOA, 5, 1);

  NVIC_SetPriority(TIMER_IRQn, 0xFF);
  NVIC_EnableIRQ(TIMER_IRQn);
  
  timer_init();
  timer_set_interrupt(0x00FF);
  while (1) {
    count = timer_count();
    count = count;
  }
}
