#include "utils.h"

// @TODO: Work for different clocks
// Assuming a 2.097Mhz clock
// THIS WILL NOT WORK FOR millis more than
void delay(uint16_t ms) {
  const int MAX = ms * 1600;
  volatile int i;
  for (i = 0; i < MAX; i++);
}

int strlen(const char* str) {
  const char* it = str;
  while(*it) {
    it++;
  }
  return it - str;
}
