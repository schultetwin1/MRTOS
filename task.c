#include "nvic.h"
#include "task.h"

typedef struct {
  void* sp;
} task_t;

task_t tasks[MAX_NUM_TASKS];
int num_tasks = 0;

static inline void save_context() {
  uint32_t scratch;
  asm volatile (
    "MRS %0, psp\n"
    "STMDB %0!, {r4-r11}\n"
    "MSR psp, %0\n" : "=r" (scratch) 
  );
}

static inline void load_context() {
  uint32_t scratch;
  asm volatile (
    "MRS %0, psp\n"
    "LDMFD %0!, {r4-r11}\n"
    "MSR psp, %0\n" : "=r" (scratch)
  );

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
