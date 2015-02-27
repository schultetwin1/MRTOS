#include "vtimer.h"
#include "gpio.h"

static vtimer_t* timer_queue = 0;
static unsigned int tick = 0;

static int insert_timer(vtimer_t* vtimer);

static inline void update_timer(vtimer_t* timer);

void  __attribute__ ((interrupt ("IRQ"))) timer_handler() {
  vtimer_t* victim;
  tick++;
  while (timer_queue && tick >= timer_queue->cb_tick) {
    victim = timer_queue;
    victim->timer_cb();
    timer_queue = timer_queue->next;
    update_timer(victim);
  }
  NVIC_ClearPendingIRQ(TIMER_IRQn);
  timer_clear_interrupt();
}

static inline void update_timer(vtimer_t* timer) {
  if (timer->num_runs != 1) {
    if (timer->num_runs > 0) {
      timer->num_runs--;
    }
    timer->cb_tick = tick + timer->ticks;
    insert_timer(timer);
  }
}

static int insert_timer(vtimer_t* vtimer) {
  vtimer_t* it;
  vtimer_t* it_prev;


  // Empty case
  if (!timer_queue) {
    timer_queue = vtimer;
    timer_queue->next = 0;
    return 0;
  }

  // Insert at front
  if (vtimer->cb_tick < timer_queue->cb_tick) {
    vtimer->next = timer_queue;
    timer_queue = vtimer;
    return 1;
  }

  // Insert anywhere else
  it = timer_queue->next;
  it_prev = timer_queue;
  while (it && it->cb_tick < vtimer->cb_tick) {
    it = it->next;
  }
  it_prev->next = vtimer;
  vtimer->next = it;
  return 2;
}

void vtimer_init() {
  timer_init();
}

void vtimer_add_timer(vtimer_t* vtimer, timer_fn_t callback, uint32_t ticks, uint32_t num_runs) {
  // @TODO: Watch for overflow
  vtimer->cb_tick = tick + ticks;
  vtimer->ticks = ticks;
  vtimer->timer_cb = callback;
  vtimer->num_runs = num_runs;

  timer_mask_interrupt();
  insert_timer(vtimer);
  timer_unmask_interrupt();
}

void vtimer_remove_timer(vtimer_t* timer) {

}

void vtimer_enable() {
  timer_enable_interrupt(20);
}

void vtimer_disable() {
  timer_disable_interrupt();
}
