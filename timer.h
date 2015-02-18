#ifndef __MRTOS_TIMER__
#define __MRTOS_TIMER__

#include <inttypes.h>

#include "nvic.h"

#define MAX_FREQ  2097000 // 2.097 MHz
#define SCALAR    0x10    // 131.1 KHz
#define TICK_TO_US 20

static const uint32_t CLK_FREQ = MAX_FREQ / SCALAR;
static const IRQn_t TIMER_IRQn;

// Currently just using timer21

void timer_init();

uint16_t timer_count();
void timer_enable_interrupt(uint16_t value);
void timer_disable_interrupt();
void timer_clear_interrupt();

void timer_mask_interrupt();
void timer_unmask_interrupt();

#endif
