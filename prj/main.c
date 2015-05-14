#include "drivers/gpio.h"
#include "task.h"
#include "utils.h"
#include "drivers/uart.h"

void uart_task(void* arg) {
  uint8_t rcv[1];

  gpio_init(GPIOA);
  gpio_set_mode(GPIOA, 5, GPIO_OUTPUT_MODE);

  uart_init();
  uart_set_wordlength(8);
  uart_set_baudrate(115200);
  uart_set_parity(UART_NO_PARITY);
  uart_set_stop_bits(UART_ONE_STOP_BIT);
  uart_enable();

  while (rcv[0] != 'a') {
    uart_recv(rcv, 1);
  }
  gpio_write(GPIOA, 5, 1);
  while (1);

}

void toggle_task(void* arg) {
  int toggle = 0;

  gpio_init(GPIOB);
  gpio_set_mode(GPIOB, 4, GPIO_OUTPUT_MODE);

  while (1) {
    toggle ^= 1;
    gpio_write(GPIOB, 4, toggle);
    delay(1000);
  }

}

int main() {

  add_task(uart_task, NULL);
  add_task(toggle_task, NULL);
  run_tasks();

  while (1);
  return 0;
}
