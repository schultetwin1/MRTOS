#include "vector.h"

extern unsigned _stack;
extern unsigned _data_loadaddr, _data, _edata, _ebss;

void blocking_handler(void);
void null_handler(void);
void main(void);

void __attribute__ ((naked)) reset_handler(void);

__attribute__ ((section(".vectors")))
vector_table_t vector_table = {
  .initial_sp_value = &_stack,
  .reset = reset_handler,
  .nmi = null_handler,
  .hard_fault = blocking_handler,
  .sv_call = null_handler,
  .pend_sv = null_handler,
  .systick = null_handler
};

void __attribute__ ((naked)) reset_handler(void)
{
  volatile unsigned *src, *dest;

  for (src = &_data_loadaddr, dest = &_data; dest < &_edata; src++, dest++) {
    *dest = *src;
  }

  while (dest < &_ebss) {
    *dest++ = 0;
  }

  main();

  while (1);
}

void blocking_handler(void) {
  while (1);
}

void null_handler(void) {

}
