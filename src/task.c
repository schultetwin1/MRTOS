#include "drivers/nvic.h"
#include "task.h"

extern void start_scheduler();
extern void port_task_yield();

typedef struct __attribute__((__packed__)) {
  uint32_t R0;
  uint32_t R1;
  uint32_t R2;
  uint32_t R3;
  uint32_t R12;
  uint32_t LR;
  uint32_t PC;
  uint32_t xPSR;
} hw_stack_frame_t;

typedef struct {
  uint8_t* sp;
} task_t;
int num_tasks = 0;
TaskID cur_task = -1;

task_t tasks[MAX_NUM_TASKS];
uint8_t stacks[MAX_NUM_TASKS][STACK_SIZE];

static void end_of_task() {
  while (1);
}

void switch_context() {
  cur_task++;
  if (cur_task == num_tasks) {
    cur_task = 0;
  }
}

TaskID add_task(FuncPtr fn, FuncArgs args) {
  hw_stack_frame_t* frame;

  if (num_tasks == MAX_NUM_TASKS) {
    return MAX_NUM_TASKS;
  }

  TaskID id = num_tasks++;
  tasks[id].sp = (uint8_t*)(((uint8_t*)&stacks[id]) + STACK_SIZE);

  // -1 in order to leave the top empty
  // (for a usual stack frame that would be the last entry from the before the interrupt)
  // @TODO: Not portable
  frame = (hw_stack_frame_t*)(tasks[id].sp - sizeof(hw_stack_frame_t) - 4);
  frame->xPSR = 0x01000000;
  frame->PC = (uint32_t)fn;
  frame->LR = (uint32_t)end_of_task;
  frame->R0 = (uint32_t)args;

  // Update sp for task
  tasks[id].sp = (uint8_t*)frame - 32;

  return id;
}

void task_yield() {
  port_task_yield();
}

void run_tasks() {
  // No tasks to run
  if (num_tasks <= 0) return;
  cur_task = 0;

  // Enable pendsv int
  NVIC_SetPriority(PEND_SV_IRQn, 0xFF);
  start_scheduler();
}
