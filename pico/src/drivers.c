#include "drivers/led.h"
#include "pico/time.h"

static int current_task_id = 0;

void
drivers_log_info(const char *message)
{
  // DO Nothing for now
}

int
drivers_time_ms(void)
{
  return (time_us_64() / 1000);
}

void
drivers_led_on(drivers_led_t led)
{
  // Do nothing for now
}

void
drivers_led_off(drivers_led_t led)
{
  // Do nothing for now
}

void drivers_led_toggle(drivers_led_t led)
{
  // Do nothing for now
}