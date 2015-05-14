#include "drivers/gpio.h"
#include "task.h"
#include "utils.h"
#include "drivers/uart.h"
#include "drivers/port_epd.h"

#include "fontsepd.h"

int main() {

  gpio_init(GPIOA);
  gpio_set_mode(GPIOA, 0, GPIO_INPUT_MODE);
  while (gpio_read(GPIOA, 0) == 0)
    ;

  epd_init();
  epd_clr();
  
  epd_draw_block(0, 0, Font20.Height, Font20.Width, Font20.table + (Font20.Height * Font20.Width * 33));
  epd_draw_block(0, Font20.Width, Font20.Height, Font20.Width, Font20.table + (Font20.Height * Font20.Width * 34));

  epd_refresh_display();

  while (1);
  run_tasks();

  while (1);
  return 0;
}
