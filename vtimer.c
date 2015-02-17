#include "vtimer.h"

static vtimer_t* timer_queue = 0;
static unsigned int tick = 0;

static void vtimer_enable();
static void vtimer_disable();

void  __attribute__ ((interrupt ("IRQ"))) timer_handler() {
  tick++;
  while (timer_queue && tick >= timer_queue->ticks) {
    timer_queue->timer_cb();
    timer_queue = timer_queue->next;
  }
  if (!timer_queue) {
    vtimer_disable();
  }
  NVIC_ClearPendingIRQ(TIMER_IRQn);
  timer_clear_interrupt();
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
  if (vtimer->ticks < timer_queue->ticks) {
    vtimer->next = timer_queue;
    timer_queue = vtimer;
    return 1;
  }

  // Insert anywhere else
  it = timer_queue->next;
  it_prev = timer_queue;
  while (it && it->ticks < vtimer->ticks) {
    it = it->next;
  }
  it_prev->next = vtimer;
  vtimer->next = it;
  return 2;
}

void vtimer_init() {
  timer_init();
}

void vtimer_add_timer(vtimer_t* vtimer, timer_fn_t callback, uint32_t ticks) {
  int rc;

  // @TODO: Watch for overflow
  vtimer->ticks = tick + ticks;
  vtimer->timer_cb = callback;

  timer_mask_interrupt();
  rc = insert_timer(vtimer);
  if (rc == 0) {
    vtimer_enable();
  }
  timer_unmask_interrupt();
}

void vtimer_remove_timer(vtimer_t* timer) {

}

static void vtimer_enable() {
  timer_enable_interrupt(0xFFFF);
}

static void vtimer_disable() {
  timer_disable_interrupt();
}
