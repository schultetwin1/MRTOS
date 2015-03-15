#include "nvic.h"
#include "task.h"

typedef struct {
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
  uint32_t R4;
  uint32_t R5;
  uint32_t R6;
  uint32_t R7;
  uint32_t R8;
  uint32_t R9;
  uint32_t R10;
  uint32_t R11;
} sw_stack_frame_t;

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

static inline uint8_t* read_psp() {
  uint8_t* psp = (uint8_t*)0;
  asm volatile ("MRS %0, psp\n" : "=r" (psp));
  return psp;
}

static inline void write_psp(uint8_t* psp) {
  asm volatile ("MSR psp, %0\n" :: "r" (psp));
}

static inline void save_context() {
  // Get task sp and make room for 8 more regs
  uint8_t* psp = read_psp();
  psp -= 32; 

  // Save stack pointer
  tasks[cur_task].sp = psp;

  // Save regs r4 - r11
  asm volatile (
    "STMIA %0!, {r4-r7}\n"
    "MOV   r4, r8\n"
    "MOV   r5, r9\n"
    "MOV   r6, r10\n"
    "MOV   r7, r11\n"
    "STMIA %0!, {r4-r7}\n"
    :
    : "r" (psp)
  );
}

static inline void load_context() {
  uint8_t* psp = tasks[cur_task].sp;

  asm volatile (
    "ADD %0, #16\n"
    "LDMIA %0!, {r4-r7}\n"
    "MOV r11, r7\n"
    "MOV r10, r6\n"
    "MOV r9, r5\n"
    "MOV r8, r4\n"

    "MSR psp, %0\n" 

    "SUB %0, #32\n"
    "LDMIA %0!, {r4-r7}\n"
    :
    : "r"(psp)
  );

}


void switch_context() {
}

TaskID add_task(FuncPtr* fn, FuncArgs* args) {
  hw_stack_frame_t* frame;

  if (num_tasks == MAX_NUM_TASKS) {
    return MAX_NUM_TASKS;
  }

  TaskID id = num_tasks++;
  tasks[id].sp = (uint8_t*)(&stacks[id] + STACK_SIZE - 1);

  // -1 in order to leave the top empty
  // (for a usual stack frame that would be the last entry from the before the interrupt)
  frame = (hw_stack_frame_t*)(tasks[id].sp - sizeof(hw_stack_frame_t) - 1);
  frame->xPSR = 0x01000000;
  frame->PC = (uint32_t)fn;
  frame->LR = (uint32_t)end_of_task;
  frame->R0 = (uint32_t)args;

  // Update sp for task
  tasks[id].sp = tasks[id].sp - sizeof(hw_stack_frame_t) - sizeof(sw_stack_frame_t);

  return id;
}

void task_yield() {
  NVIC_SetPendingIRQ(PEND_SV_IRQn);
}

void pend_sv_handler() {
  save_context();
  switch_context();
  load_context();
  NVIC_ClearPendingIRQ(PEND_SV_IRQn);
}
