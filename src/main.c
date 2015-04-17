#include "drivers/gpio.h"
#include "drivers/nvic.h"
#include "task.h"
#include "drivers/timer.h"
#include "utils.h"
#include "vtimer.h"
#include "drivers/uart.h"

void toggle_ledA() {
  static int toggle = 0;
  gpio_write(GPIOA, 5, toggle);
  toggle ^= 1;
  delay(1000);
}

void toggle_ledB(void* args) {
  //int toggle = 0;
  while (1) {
    gpio_write(GPIOA, 5, 0);
    //toggle ^= 1;
    //delay(1000);
  }
}

int main() {
  uint8_t snd[1];
  uint8_t rcv[1];
  gpio_init(GPIOA);
  gpio_init(GPIOB);
  
  gpio_set_mode(GPIOA, 5, GPIO_OUTPUT_MODE);
  gpio_set_mode(GPIOB, 4, GPIO_OUTPUT_MODE);

  uart_init();
  uart_set_wordlength(8);
  uart_set_baudrate(115200);
  uart_set_parity(UART_NO_PARITY);
  uart_set_stop_bits(UART_ONE_STOP_BIT);
  uart_enable();

  snd[0] = 'a';

  while (1) {
    uart_send(snd, 1);
    uart_recv(rcv, 1);
    if ('a' == rcv[0]) {
      toggle_ledA();
    }
  }

  //run_tasks();

  // Should never hit here
  while (1);
  return 0;
}
