#ifndef __MRTOS_RTC__
#define __MRTOS_RTC__
#include "drivers/port_rtc.h"

void rtc_init();
void rtc_set_time();
void rtc_read_time(char* buf);
void rtc_read_date(char* buf);

void rtc_set_periodic_wakeup();
uint8_t rtc_timer();
#endif
