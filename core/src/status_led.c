#include "drivers/time.h"
#include "drivers/led.h"

#include "core/status_led.h"

enum status_led_state {
  CORE_STATUS_LED_ON,
  CORE_STATUS_LED_OFF
};

struct {
  int last_update_time;
  int blink_count;
  enum status_led_state current_state;
} success_led_state = {0, 0, CORE_STATUS_LED_OFF};


static void
core_status_led_run_success_led_task(void)
{
  if (!success_led_state.blink_count)
  {
    return; // Task not running
  }

  int now = drivers_time_ms();
  int time_since_last_update = now - success_led_state.last_update_time;

  if (success_led_state.current_state == CORE_STATUS_LED_ON)
  {
    if (time_since_last_update >= CORE_STATUS_LED_SUCCESS_DURATION_MS)
    {
      drivers_led_off(DRIVERS_LED_SUCCESS);
      success_led_state.current_state = CORE_STATUS_LED_OFF;

    }
  } else if (success_led_state.current_state == CORE_STATUS_LED_OFF)
  {
    if (time_since_last_update >= CORE_STATUS_LED_TASK_INTERVAL_MS || !success_led_state.last_update_time)
    {
      drivers_led_on(DRIVERS_LED_SUCCESS);
      success_led_state.current_state = CORE_STATUS_LED_ON;
      success_led_state.last_update_time = now;
      success_led_state.blink_count--;
    }
  }
}

void
core_status_led_run_tasks(void)
{
  core_status_led_run_success_led_task();
}

int
core_status_led_success(void)
{

  if (success_led_state.blink_count)
  {
    return -1; // Task already running
  }

  success_led_state.blink_count = CORE_STATUS_LED_SUCCESS_BLINK_COUNT;
  success_led_state.last_update_time = drivers_time_ms();

  return 0; // Task started successfully
}