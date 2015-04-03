#include <inttypes.h>

#include "task.h"
#include "port.h"

#include "drivers/nvic.h"
#include "drivers/port_systick.h"

void pend_sv_handler() __attribute__((naked, interrupt));
extern void switch_context();

static uint32_t PRIMASK;

inline void port_critical_start() {
  asm volatile(
    "mrs r0, PRIMASK\n"
    "mov %[MASK], r0\n"
    "cpsid i \n"
    : [MASK] "=r" (PRIMASK)
    :
    : "r0"
  );
}

inline void port_critical_end() {
  asm volatile(
    "mov r0, %[MASK]\n"
    "msr primask, r0\n"
    :
    : [MASK] "r" (PRIMASK)
    : "r0"
  );
}

inline void port_task_yield() {
  NVIC_SetPendingIRQ(PEND_SV_IRQn);
}

void systick_handler() {
  port_task_yield();
  NVIC_ClearPendingIRQ(SYSTICK_IRQn);
}

void pend_sv_handler() {
  uint8_t* psp;
  asm volatile(
    "push {lr}\n"
    /**
     Storing context
     */
    /* Load sp from status reg */
    "MRS %[psp], PSP\n"

    /* Make room for 8 more regs */
    "SUB %[psp], #32\n"

    /* Push r4-r11 onto that stack as well */
    "STMIA %[psp]!, {r4-r7}\n"
    "MOV   r4, r8\n"
    "MOV   r5, r9\n"
    "MOV   r6, r10\n"
    "MOV   r7, r11\n"
    "STMIA %[psp]!, {r4-r7}\n"
    "SUB %[psp], #32\n"
    : [psp] "=r" (psp)
    :
    : "r4", "r5", "r6", "r7"
  );

  port_critical_start();
  tasks[cur_task_id].sp = psp;
  switch_context();
  psp = tasks[cur_task_id].sp;
  NVIC_ClearPendingIRQ(PEND_SV_IRQn);
  port_critical_end();

  asm volatile (
    /**
     Loading context
     */
    /* Load r8 - r11 */
    "ADD %[psp], #16\n"
    "LDMIA %[psp]!, {r4-r7}\n"
    "MOV r11, r7\n"
    "MOV r10, r6\n"
    "MOV r9, r5\n"
    "MOV r8, r4\n"

    /* set new sp */
    "MSR psp, %[psp]\n"

    /* load r4 - r7 */
    "SUB %[psp], #32\n"
    "LDMIA %[psp]!, {r4-r7}\n"

    "pop {pc}\n"
    :
    : [psp] "r" (psp)
    : "r4", "r5", "r6", "r7", "r8", "r9", "r10", "r11"
  );
}

void port_start_scheduler() {
  uint8_t* psp;
  uint32_t ctrl;
  switch_context();

  // Enable pendsv int
  NVIC_SetPriority(PEND_SV_IRQn, 0xFF);

  // Setup systick
  systick_init();

  psp = tasks[cur_task_id].sp;

  psp = psp + 32;
  asm (
    "MSR psp, %[psp]\n"
    :
    : [psp] "r" (psp)
  );

  ctrl = 2;
  asm  (
    "MSR control, %[ctrl]\n"
    :
    : [ctrl] "r" (ctrl)
  );

  port_critical_end();

  asm volatile (
    "POP {r0-r5}\n"
    "MOV lr, r5\n"
    "POP {pc}\n"
    :
    :
    : "r0", "r1", "r2", "r3", "r4", "r5", "lr"
  );
}

uint8_t* port_init_stack(uint8_t* sp, FuncPtr fn, FuncArgs args, FuncPtr lr) {
  // -1 in order to leave the top empty
  // (for a usual stack frame that would be the last entry from the before the interrupt)
  uint32_t* wsp = (uint32_t*)sp;
  wsp -= 1;

  *wsp = 0x01000000;
  wsp -= 1;

  *wsp = (uint32_t)fn;
  wsp -= 1;

  *wsp = (uint32_t)lr;
  wsp -= 5;

  *wsp = (uint32_t)args;
  wsp -= 8;

  return (uint8_t*)wsp;
}
