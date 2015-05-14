#ifndef __MRTOS_TASK__
#define __MRTOS_TASK__

#include <inttypes.h>

#define MAX_NUM_TASKS 10
#define STACK_SIZE 0x100
typedef void (*FuncPtr)( void* );
typedef void*  FuncArgs;
typedef int    TaskID;

#include "port.h"

typedef struct {
  uint8_t id;
  uint8_t* sp;
} task_t;

extern TaskID cur_task_id;
extern task_t tasks[MAX_NUM_TASKS];

TaskID add_task(FuncPtr fn, FuncArgs args);
void task_yield();
void __attribute__ ((interrupt("ISR"))) pend_sv_handler();

// Does not return
void   run_tasks();
#endif
