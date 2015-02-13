#include "timer.h"

void timer_init() {
  // enables the apb2 clock
  *((uint32_t *)(0X40021000 + 0x38)) |= (1 << 0);

  // enable the counter
  *((uint16_t *)(0X40000000 + 0x0)) |= (1 << 0);

  // set the reload register
  *((uint16_t *)(0X40000000 + 0x2C)) = 0xFFFF;

}

uint16_t timer_count() {
  return *((uint16_t *)(0X40000000 + 0x24));
}
