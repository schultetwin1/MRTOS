#ifndef __MRTOS_PORT__
#define __MRTOS_PORT__

#include "task.h"

void port_critical_start();
void port_critical_end();
void port_start_scheduler() __attribute__((naked));

uint8_t* port_init_stack(uint8_t* sp, FuncPtr fn, FuncArgs args, FuncPtr lr);
void port_task_yield();

#endif
