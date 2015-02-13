#ifndef __STM32L0_VECTOR__
#define __STM32L0_VECTOR__

#include "nvic.h"

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

void set_irq_handler(IRQn_t IRQn, vector_table_entry_t handler);
#endif
