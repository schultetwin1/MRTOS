#ifndef __MRTOS_TIMER__
#define __MRTOS_TIMER__

#include <inttypes.h>

#include "nvic.h"

// Currently assumes 16-bit timer

void timer_init();

uint16_t timer_count();
void timer_enable_interrupt(uint16_t value);
void timer_disable_interrupt();
void timer_clear_interrupt();

void timer_mask_interrupt();
void timer_unmask_interrupt();

#endif
