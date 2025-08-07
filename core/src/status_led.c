#include "drivers/time.h"
#include "drivers/led.h"
#include "drivers/log.h"

#include "core/status_led.h"

enum core_status_led_state
{
  CORE_STATUS_LED_OFF,
  CORE_STATUS_LED_ON,
};

struct core_status_led
{
  int cycle_start_time; // Time when the current cycle started
  int remaining_cycles; // Number of cycles left to complete
  int cycles_started;   // Number of cycles that have been started
  enum core_status_led_state current_state; // Current state of the LED
};

static struct core_status_led success_led_state = {0, 0, 0, CORE_STATUS_LED_OFF};

int
core_status_led_init(void)
{
  return drivers_led_init(DRIVERS_LED_SUCCESS);
}

static void
core_status_led_run_success_led_task(void)
{

  drivers_log_debug("core_status_led_run_success_led_task: remaining_cycles=%d, current_state=%d",
                   success_led_state.remaining_cycles, success_led_state.current_state);

  int is_on = success_led_state.current_state == CORE_STATUS_LED_ON;

  if (!success_led_state.remaining_cycles && !is_on)
  { 
    return; // Task not running
  }

  int now = drivers_time_ms();
  int current_cycle_duration = now - success_led_state.cycle_start_time;
  int cycle_completed = current_cycle_duration >= CORE_STATUS_LED_TASK_INTERVAL_MS;

  if (is_on && current_cycle_duration >= CORE_STATUS_LED_SUCCESS_DURATION_MS)
  {
    drivers_led_off(DRIVERS_LED_SUCCESS);
    success_led_state.current_state = CORE_STATUS_LED_OFF;
  }
  else if (!is_on && (cycle_completed || !success_led_state.cycles_started)) {
      drivers_led_on(DRIVERS_LED_SUCCESS);
      success_led_state.current_state = CORE_STATUS_LED_ON;
      success_led_state.cycle_start_time = now;
      success_led_state.remaining_cycles--;
      success_led_state.cycles_started++;
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

  if (success_led_state.remaining_cycles)
  {
    return -1; // Task already running
  }

  success_led_state.remaining_cycles = CORE_STATUS_LED_SUCCESS_BLINK_COUNT;
  success_led_state.cycle_start_time = drivers_time_ms();
  success_led_state.cycles_started = 0;

  return 0; // Task started successfully
}
