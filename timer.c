#include "timer.h"

void timer_init() {
  // enables the apb2 clock
  *((uint32_t *)(0X40021000 + 0x34)) |= (1 << 2);

  // set the reload register
  *((uint16_t *)(0X40010800 + 0x2C)) = 0xFFFF;

  // enable the counter
  *((uint16_t *)(0X40010800 + 0x0)) |= (1 << 0);

}

uint16_t timer_count() {
  return *((uint16_t *)(0X40010800 + 0x24));
}

void timer_set_interrupt(uint16_t value) {
  // enable interrupts
  *((uint16_t *)(0X40010800 + 0x0C)) |= (0x1 << 1);

  // set the compare value
  *((uint16_t *)(0X40010800 + 0x34)) = value;
}
