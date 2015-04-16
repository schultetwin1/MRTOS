#ifndef __MRTOS_UART__
#define __MRTOS_UART__
#include "drivers/port_uart.h"
#include <stddef.h>
#include <inttypes.h>

void uart_init();
void uart_send(uint8_t* data, size_t len);

#endif
