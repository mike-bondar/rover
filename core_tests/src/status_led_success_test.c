#include <assert.h>
#include "core/status_led.h"
#include "drivers/led.h"
#include "drivers/log.h"

#include <stdarg.h>
#include <stdio.h>

struct {
  int success_led;
} leds = { 0 };

int
drivers_led_init(drivers_led_t led)
{
  switch (led) {
    case DRIVERS_LED_SUCCESS:
      leds.success_led = 0; // Initialize the success LED to off
      break;
    default:
      assert(0 && "Unknown LED");
  }

  return 0;
}

void
drivers_led_on(drivers_led_t led)
{
  switch (led) {
    case DRIVERS_LED_SUCCESS:
      leds.success_led = 1;
      break;
    default:
      assert(0 && "Unknown LED");
  }
}

void
drivers_led_off(drivers_led_t led)
{
  switch (led) {
    case DRIVERS_LED_SUCCESS:
      leds.success_led = 0;
      break;
    default:
      assert(0 && "Unknown LED");
  }
}

void
drivers_led_toggle(drivers_led_t led)
{
  switch (led) {
    case DRIVERS_LED_SUCCESS:
      leds.success_led = !leds.success_led;
      break;
    default:
      assert(0 && "Unknown LED");
  }
}

static int curret_time_ms = 0;

int
drivers_time_ms(void)
{
  return curret_time_ms;
}

void
drivers_log_debug(const char *message, ...)
{
  char buffer[256];
  va_list args;
  va_start(args, message);
  printf("DEBUG: ");
  vprintf(message, args);
  printf("\n");
  fflush(stdout);
  va_end(args);
}

int
main(void)
{
  // Test the initial state of the success LED
  core_status_led_run_tasks();
  assert(leds.success_led == 0);

  core_status_led_success();

  // Test first blink

  // The LED should be on after calling success and running tasks
  core_status_led_run_tasks();
  assert(leds.success_led == 1);

  // The LED should still be on before it's time to turn it off
  curret_time_ms = CORE_STATUS_LED_SUCCESS_DURATION_MS - 1;
  core_status_led_run_tasks();
  assert(leds.success_led == 1);

  // Success LED should turn off after the specific duration
  curret_time_ms += 1; // Move time forward to trigger the off condition
  core_status_led_run_tasks();
  assert(leds.success_led == 0);

  // Success LED should not turn on again if called before the next cycle
  curret_time_ms = CORE_STATUS_LED_TASK_INTERVAL_MS - 1;
  core_status_led_run_tasks();
  assert(leds.success_led == 0);

  // Test second blink

  // Success LED should turn on again after the task interval
  curret_time_ms = CORE_STATUS_LED_TASK_INTERVAL_MS;
  core_status_led_run_tasks();
  assert(leds.success_led == 1);

  curret_time_ms = CORE_STATUS_LED_TASK_INTERVAL_MS + CORE_STATUS_LED_SUCCESS_DURATION_MS - 1;
  core_status_led_run_tasks();
  assert(leds.success_led == 1);

  curret_time_ms = CORE_STATUS_LED_TASK_INTERVAL_MS + CORE_STATUS_LED_SUCCESS_DURATION_MS;
  core_status_led_run_tasks();
  assert(leds.success_led == 0);

  // Test third blink

  // Success LED should turn on again after the task interval
  curret_time_ms = CORE_STATUS_LED_TASK_INTERVAL_MS * 2;
  core_status_led_run_tasks();
  assert(leds.success_led == 1);

  curret_time_ms = (CORE_STATUS_LED_TASK_INTERVAL_MS * 2) + CORE_STATUS_LED_SUCCESS_DURATION_MS - 1;
  core_status_led_run_tasks();
  assert(leds.success_led == 1);

  curret_time_ms = (CORE_STATUS_LED_TASK_INTERVAL_MS * 2) + CORE_STATUS_LED_SUCCESS_DURATION_MS;
  core_status_led_run_tasks();
  assert(leds.success_led == 0);


  return 0;
}