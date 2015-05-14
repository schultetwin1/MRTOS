#include "task.h"
#include "utils.h"
#include "drivers/uart.h"
#include "drivers/port_epd.h"
#include "drivers/rtc.h"
#include "drivers/gpio.h"

#include "font.h"

void update_time(void* arg) {
  char buf[64];
  rtc_init();
  rtc_set_time();
  rtc_set_periodic_wakeup();
  rtc_read_date(buf);
  epd_init();
  epd_clr();
  font_drawstr(buf, 4);
  rtc_read_time(buf);
  font_drawstr(buf, 10);
  epd_refresh_display();

  while (1) {
    if (rtc_timer()) {
      rtc_read_time(buf);
      epd_clr();
      font_drawstr(buf, 10);
      rtc_read_date(buf);
      font_drawstr(buf, 4);
      epd_refresh_display();
    }
  }

}

void blink_led(void* arg) {
  int out  = 0;
  gpio_init(GPIOA);
  gpio_set_mode(GPIOA, 5, GPIO_OUTPUT_MODE);
  while (1) {
    gpio_write(GPIOA, 5, out);
    out ^= 1;
    delay(1000);
  }

}

int main() {
  add_task(update_time, NULL);
  add_task(blink_led, NULL);
  run_tasks();

  while (1);
  return 0;
}
