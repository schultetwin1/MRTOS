#ifndef __MRTOS_TIMER__
#define __MRTOS_TIMER__

#include <inttypes.h>

#define MAX_FREQ  2097000
#define SCALAR    0x100
static const uint32_t CLK_FREQ = MAX_FREQ / SCALAR;

// Currently just using timer21

void timer_init();

uint16_t timer_count();
void timer_set_interrupt(uint16_t value);
void timer_clear_interrupt();

#endif
