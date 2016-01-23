#ifndef __MRTOS_UART__
#define __MRTOS_UART__
#include "drivers/port_uart.h"
#include <stddef.h>
#include <inttypes.h>

typedef enum {
  UART_NO_PARITY,
  UART_EVEN_PARITY,
  UART_ODD_PARITY
} uart_parity_t;

typedef enum {
  UART_ONE_STOP_BIT,
  UART_ONE_POINT_FIVE_STOP_BIT,
  UART_TWO_STOP_BIT
} uart_stop_bit_t;

void uart_init();
void uart_enable();
void uart_disable();

void uart_set_baudrate(unsigned baudrate);
void uart_set_wordlength(int wordlength);
void uart_set_parity(uart_parity_t parity);
void uart_set_stop_bits(uart_stop_bit_t stopbit);

void uart_send(uint8_t* data, size_t len);
void uart_recv(uint8_t* data, size_t len);

#endif
