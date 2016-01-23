#ifndef __MRTOS_PORT_PWR__
#define __MRTOS_PORT_PWR__
#define PWR_DBP (1 << 8)
typedef volatile struct {
  uint32_t CR;
  uint32_t CSR;
} pwr_t;

static pwr_t volatile * const PWR  = (pwr_t  volatile * const)(0X40007000);
#endif
