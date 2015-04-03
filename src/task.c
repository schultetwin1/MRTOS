#include "drivers/nvic.h"
#include "task.h"

int num_tasks = 0;
TaskID cur_task_id = -1;

task_t tasks[MAX_NUM_TASKS];
uint8_t stacks[MAX_NUM_TASKS][STACK_SIZE];

static void end_of_task() {
  while (1);
}

void switch_context() {
  cur_task_id++;
  if (cur_task_id == num_tasks) {
    cur_task_id = 0;
  }
}

TaskID add_task(FuncPtr fn, FuncArgs args) {
  if (num_tasks == MAX_NUM_TASKS) {
    return MAX_NUM_TASKS;
  }

  TaskID id = num_tasks++;
  tasks[id].sp = (uint8_t*)(((uint8_t*)&stacks[id]) + STACK_SIZE);

  tasks[id].sp = port_init_stack(tasks[id].sp, fn, args, end_of_task);

  return id;
}

void task_yield() {
  port_task_yield();
}

void run_tasks() {
  // No tasks to run
  if (num_tasks <= 0) return;

  port_start_scheduler();
}
