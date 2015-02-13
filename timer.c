#include "timer.h"

void timer_init() {
  *((unsigned *)(0X40021000 + 0x28)) |= (1 << 0);
}
