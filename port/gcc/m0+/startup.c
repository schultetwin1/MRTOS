#include "drivers/port_rcc.h"
#include "drivers/nvic.h"
#include "port.h"

extern unsigned _stack;
extern unsigned _data_loadaddr, _data, _edata, _ebss;
extern void timer_handler(void);
extern void pend_sv_handler(void);
extern void systick_handler(void);

typedef void (*vector_table_entry_t)(void);

#define NUM_IRQS 32

typedef struct {
  unsigned int *initial_sp_value;
  vector_table_entry_t reset;
  vector_table_entry_t nmi;
  vector_table_entry_t hard_fault;
  vector_table_entry_t reserved1[7];
  vector_table_entry_t sv_call;
  vector_table_entry_t reserved2[2];
  vector_table_entry_t pend_sv;
  vector_table_entry_t systick;
  vector_table_entry_t reserved3;
  vector_table_entry_t IRQ[NUM_IRQS];
} vector_table_t;

void blocking_handler(void);
void null_handler(void);
void hard_fault_handler(void);
void nmi_handler(void);
void sv_call_handler(void);
void main(void);

void  __attribute__ ((interrupt ("IRQ"), naked)) reset_handler(void);

__attribute__ ((section(".vectors")))
vector_table_t vector_table = {
  .initial_sp_value = &_stack,
  .reset = reset_handler,
  .nmi = nmi_handler,
  .hard_fault = hard_fault_handler,
  .sv_call = sv_call_handler,
  .pend_sv = pend_sv_handler,
  .systick = systick_handler,
  .IRQ = {
    blocking_handler, // 0
    blocking_handler, // 1
    blocking_handler, // 2
    blocking_handler, // 3
    blocking_handler, // 4
    blocking_handler, // 5
    blocking_handler, // 6
    blocking_handler, // 7
    blocking_handler, // 8
    blocking_handler, // 9
    blocking_handler, // 10
    blocking_handler, // 11
    blocking_handler, // 12
    blocking_handler, // 13
    blocking_handler, // 14
    blocking_handler, // 15
    blocking_handler, // 16
    blocking_handler, // 17
    blocking_handler, // 18
    timer_handler    // 19
  }
};

void reset_handler(void)
{
  volatile unsigned *src, *dest;

  // Initialize data from flash
  for (src = &_data_loadaddr, dest = &_data; dest < &_edata; src++, dest++) {
    *dest = *src;
  }

  // Initialize zero'd data
  while (dest < &_ebss) {
    *dest++ = 0;
  }

  // Disable all interrupts
  port_critical_start();

  // Switch to 16MHz clk
  rcc_hsi16_enable();
  rcc_switch_sys_clk(SYSCLK_HSI16);

  main();

  while (1);
}

void  __attribute__ ((interrupt ("IRQ"))) blocking_handler(void) {
  while (1);
}

void  __attribute__ ((interrupt ("IRQ"))) null_handler(void) {

}

void  __attribute__ ((interrupt ("IRQ"))) hard_fault_handler(void) {
  while (1);
}

void __attribute__ ((interrupt ("IRQ"))) nmi_handler(void) {
  while (1);
}

void __attribute__ ((interrupt ("IRQ"))) sv_call_handler(void) {
  while (1);
}
