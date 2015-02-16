#include "vtimer.h"

static vtimer_t* timer_queue = 0;

void vtimer_init() {
  timer_init();
}

void add_timer(vtimer_t* vtimer, uint16_t ticks) {

}
