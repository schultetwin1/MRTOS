#include <inttypes.h>

#include "utils.h"

// Assuming a 2.097Mhz clock
// THIS WILL NOT WORK FOR millis more than
void busy_loop(uint16_t millis) {
  int MAX = millis * 209;
  volatile int i;
  for (i = 0; i < MAX; i++);
}
