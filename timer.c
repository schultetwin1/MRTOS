#include "timer.h"

typedef struct {
  // 0x00
  uint16_t TIMx_CR1;
  uint16_t _reserved0;

  // 0x04
  uint16_t TIMx_CR2;
  uint16_t _reserved1;

  // 0x08
  uint32_t TIMx_SMCR;

  // 0x0C
  uint8_t TIMx_DIER;
  uint8_t _reserved2;
  uint8_t _reserved3;
  uint8_t _reserved4;

  // 0X10
  uint16_t TIMx_SR;
  uint16_t _reserved5;

  // 0x14
  uint8_t TIMx_EGR;
  uint8_t _reserved6;
  uint8_t _reserved7;
  uint8_t _reserved8;

  // 0x18
  uint16_t TIMx_CCMR1_OUTPUT;
  uint16_t TIMx_CCMR1_INPUT;

  // 0x1C
  uint32_t _reserved9;

  // 0x20
  uint8_t TIMx_CCER;
  uint8_t _reserved10;
  uint8_t _reserved11;
  uint8_t _reserved12;

  // 0x24
  uint16_t TIMx_CNT;
  uint16_t _reserved13;

  // 0x28
  uint16_t TIMx_PSC;
  uint16_t _reserved14;

  // 0x2C
  uint16_t TIMx_ARR;
  uint16_t _reserved15;

  // 0x30
  uint32_t _reserved16;

  // 0x34
  uint16_t TIMx_CCR1;
  uint16_t _reserved17;

  // 0x38
  uint16_t TIMx_CCR2;
  uint16_t _reserved18;

  // 0x3C - 4C
  uint32_t _reserved19;
  uint32_t _reserved20;
  uint32_t _reserved21;
  uint32_t _reserved22;

  // 0x50
  uint8_t TIM_OR;
  uint8_t _reserved23;
  uint8_t _reserved24;
  uint8_t _reserved25;

} TIM21_22_t;

static TIM21_22_t * const TIM21 = (TIM21_22_t * const)0X40010800;

void timer_init() {
  // enables the apb2 clock
  *((uint32_t *)(0X40021000 + 0x34)) |= (1 << 2);

  // set the reload register
  // *((uint16_t *)(0X40010800 + 0x2C)) = 0xFFFF;
  TIM21->TIMx_ARR = 0x0000FFFF;

  // set the prescalar register
  //*((uint16_t *)(0X40010800 + 0x28)) = SCALAR;
  TIM21->TIMx_PSC = SCALAR;

  // enable the counter
  //*((uint16_t *)(0X40010800 + 0x0)) |= (1 << 0);
  TIM21->TIMx_CR1 |= (1 << 0);
}

uint16_t timer_count() {
  //return *((uint16_t *)(0X40010800 + 0x24));
  return TIM21->TIMx_CNT;
}

void timer_set_interrupt(uint16_t value) {
  // enable interrupts
  //*((uint16_t *)(0X40010800 + 0x0C)) |= (0x1 << 1);
  TIM21->TIMx_DIER |= (1 << 1);

  // set the compare value
  // *((uint16_t *)(0X40010800 + 0x34)) = value;
  TIM21->TIMx_CCR1 = value;
}

void timer_clear_interrupt() {
  // clear interrupt
  //*((uint16_t *)(0X40010800 + 0x10)) &= ~(0x1 << 1);
  TIM21->TIMx_SR &= ~(1 << 1);
}
