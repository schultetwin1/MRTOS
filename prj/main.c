#include "drivers/gpio.h"
#include "task.h"
#include "utils.h"
#include "drivers/uart.h"
#include "drivers/port_epd.h"
#include "drivers/rtc.h"

#include "font.h"

int main() {
  char buf[6];
  rtc_init();
  rtc_set_time();
  rtc_set_periodic_wakeup();
  rtc_read_time(buf);
  epd_init();
  epd_clr();
  font_drawstr(buf);
  epd_refresh_display();

  while (1) {
    if (rtc_timer()) {
      rtc_read_time(buf);
      font_drawstr(buf);
      epd_refresh_display();
    }
  }
  run_tasks();

  while (1);
  return 0;
}
