#include "drivers/nvic.h"

void port_task_yield() {
  NVIC_SetPendingIRQ(PEND_SV_IRQn);
}
