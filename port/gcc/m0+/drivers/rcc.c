#include "drivers/port_rcc.h"

void rcc_hsi16_enable() {
  RCC->RCC_CR |= 0x1;
}

void rcc_switch_sys_clk(sysclk_src_t src) {
  uint32_t cfgr = RCC->RCC_CFGR;
  cfgr &= ~(0x3);
  cfgr |= src;
  RCC->RCC_CFGR = cfgr;
}

void rcc_gpio_clk_enable(uint8_t port) {
  RCC->RCC_IOPENR |= (1 << port);
}
