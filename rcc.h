#ifndef __MRTOS_RCC__
#define __MRTOS_RCC__
#include <inttypes.h>

typedef enum {
  SYSCLK_MSI = 0,
  SYSCLK_HSI16 = 1,
  SYSCLK_HSE = 2,
  SYSCLK_PLL = 3
} sysclk_src_t;

void rcc_hsi16_enable();
void rcc_switch_sys_clk(sysclk_src_t src);
void rcc_gpio_clk_enable(uint8_t port);
#endif
