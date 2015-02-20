#include "rcc.h"

#define RCC_ADDR 0x40021000

typedef volatile struct {
  // 0x00
  uint32_t RCC_CR;

  // 0x04
  uint32_t RCC_ICSCR;

  // 0x08
  uint32_t RCC_CRRCR;

  // 0x0C
  uint32_t RCC_CFGR;

  // 0x10
  uint8_t RCC_CIER;
  uint8_t _reserved1;
  uint8_t _reserved2;
  uint8_t _reserved3;

  // 0x14
  uint16_t RCC_CIFR;
  uint16_t _reserved4;

  // 0x18
  uint16_t RCC_CICR;
  uint16_t _reserved5;

  // 0x1C
  uint8_t RCC_IOPRSTR;
  uint8_t _reserved6;
  uint8_t _reserved7;
  uint8_t _reserved8;

  // 0x20
  uint32_t RCC_AHBRSTR;

  // 0x24
  uint32_t RCC_APB2RSTR;

  // 0x28
  uint32_t RCC_APB1RSTR;

  // 0x2C
  uint8_t RCC_IOPENR;
  uint8_t _reserved9;
  uint8_t _reserved10;
  uint8_t _reserved11;

  // 0x30
  uint32_t RCC_AHBENR;

  // 0x34
  uint32_t RCC_APB2ENR;

  // 0x38
  uint32_t RCC_APB1ENR;

  // 0x3C
  uint8_t RCC_IOPSMEN;
  uint8_t _reserved12;
  uint8_t _reserved13;
  uint8_t _reserved14;

  // 0x40
  uint32_t RCC_AHBSMENR;

  // 0x44
  uint32_t RCC_APBSMENR;

  // 0x48
  uint32_t RCC_APB1_SMENR;

  // 0x4C
  uint32_t RCC_CCIPR;

  // 0x50
  uint32_t RCC_CSR;
} rcc_t;

rcc_t * const RCC = (rcc_t * const)(RCC_ADDR);

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
