#ifndef __MRTOS_PORT__
#define __MRTOS_PORT__

#include "task.h"

void critical_start();
void critical_end();

uint8_t* port_init_stack(uint8_t* sp, FuncPtr fn, FuncArgs args, FuncPtr lr);
void port_task_yield();

#endif
