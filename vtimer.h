#ifndef __MRTOS_VTIMER__
#define __MRTOS_VTIMER__
#include "timer.h"

typedef void (*timer_fn_t)(void);

typedef struct vtimer vtimer_t;

struct vtimer {
  vtimer_t* next;
  timer_fn_t timer_cb;
  uint16_t ticks;
  uint16_t cb_tick;
  uint32_t num_runs;
};

void vtimer_init();

void vtimer_add_timer(vtimer_t* vtimer, timer_fn_t callback, uint32_t ticks, uint32_t num_runs);
void vtimer_remove_timer(vtimer_t* timer);

#endif
