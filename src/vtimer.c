#include "vtimer.h"
#include "drivers/gpio.h"
#include "priority_queue.h"

static priority_queue_t timer_queue;
static const unsigned MAX_NUM_VTIMERS = 100;
static block_t vtimers_queue[MAX_NUM_VTIMERS];
static unsigned int tick = 0;

static inline void update_timer(vtimer_t* timer);

void  __attribute__ ((interrupt ("IRQ"))) timer_handler() {
  vtimer_t* victim;
  tick++;
  while (priority_queue_size(&timer_queue) != 0 && tick >= ((vtimer_t*)(priority_queue_peek(&timer_queue)))->cb_tick) {
    victim = (vtimer_t*)priority_queue_pop(&timer_queue);
    victim->timer_cb();
    update_timer(victim);
  }
  timer_clear_interrupt();
  NVIC_ClearPendingIRQ(TIMER_IRQn);
}

static inline void update_timer(vtimer_t* timer) {
  if (timer->num_runs != 1) {
    if (timer->num_runs > 0) {
      timer->num_runs--;
    }
    timer->cb_tick = tick + timer->ticks;
    priority_queue_insert(&timer_queue, (node_t*)timer, vtimer_cmp);
  }
}

void vtimer_init() {
  priority_queue_init(&timer_queue, vtimer_cmp, &vtimers_queue, MAX_NUM_VTIMERS);
  timer_init();
}

void vtimer_add_timer(vtimer_t* vtimer, timer_fn_t callback, uint32_t ticks, uint32_t num_runs) {
  // @TODO: Watch for overflow
  vtimer->cb_tick = tick + ticks;
  vtimer->ticks = ticks;
  vtimer->timer_cb = callback;
  vtimer->num_runs = num_runs;

  timer_mask_interrupt();
  priority_queue_insert(&timer_queue, vtimer);
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

int vtimer_cmp(void* a, void* b) {
  return ((vtimer_t*)(a))->cb_tick - ((vtimer_t*)(b))->cb_tick;
}
