#include "nvic.h"
#include "task.h"

static inline void save_context() {

}

static inline void load_context() {

}

TaskID add_task(FuncPtr* fn, FuncArgs* args) {
  // @TODO
  return 0;
}

// Pretty sure this is wrong, but I want to check to see if this works
void task_yield() {
  NVIC_SetPendingIRQ(PEND_SV_IRQn);
}

void pend_sv_handler() {
  save_context();
  load_context();
}
