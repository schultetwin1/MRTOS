#include <inttypes.h>

#include "utils.h"

// @TODO: Work for different clocks
// Assuming a 2.097Mhz clock
// THIS WILL NOT WORK FOR millis more than
void delay(uint16_t ms) {
  const int MAX = ms * 209;
  volatile int i;
  for (i = 0; i < MAX; i++);
}
