#ifndef __MRTOS_VTIMER__
#define __MRTOS_VTIMER__
#include "timer.h"

typedef void (*timer_fn_t)(void);

typedef struct {
  timer_fn_t timer_cb;
  uint16_t ticks;
  vtimer_t* next;
} vtimer_t;

void vtimer_init();

void add_timer(timer_fn_t timer_cb, uint16_t ticks);

#endif
