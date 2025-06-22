#include "drivers/led.h"
#include "pico/time.h"

#include "pico/led.h"
#include "pico/stdlib.h"

static int current_task_id = 0;

void
drivers_log_info(const char *message)
{
  // DO Nothing for now
}

void
drivers_log_debug(const char *message, ...)
{
  // Do nothing for now
}

int
drivers_time_ms(void)
{
  return (time_us_64() / 1000);
}

int
drivers_led_init(drivers_led_t led)
{
  switch (led)
  {
    case DRIVERS_LED_SUCCESS:
      gpio_init(PICO_LED_SUCCESS_PIN);
      gpio_set_dir(PICO_LED_SUCCESS_PIN, GPIO_OUT);
      return 0;
    default:
      // Handle unknown LED case
      return -1;
  }
  // Do nothing for now
  return 0;
}

void
drivers_led_on(drivers_led_t led)
{
  switch (led)
  {
  case DRIVERS_LED_SUCCESS:
    gpio_put(PICO_LED_SUCCESS_PIN, 1);
    break;
  default:
  }
}

void
drivers_led_off(drivers_led_t led)
{
  switch (led)
  {
  case DRIVERS_LED_SUCCESS:
    gpio_put(PICO_LED_SUCCESS_PIN, 0);
    break;
  default:
  }
}