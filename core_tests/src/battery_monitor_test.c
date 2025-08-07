#include "core/battery_monitor.h"
#include <stdarg.h>
#include <stdio.h>
#include <assert.h>

static int current_adc_val = -1;

void
drivers_adc_init(void)
{
  current_adc_val = -1;
}

int
drivers_adc_pull_latest(void)
{
  return current_adc_val;
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
  assert(core_battery_monitor_get_status() == CORE_BATTERY_NOT_READY);

  // 9 items goes into buffer - the battery monitor shouldn't be ready yet
  int adc = 700;
  for (int i = 0; i < 15; i++)
  {
    current_adc_val = adc++;
    core_battery_monitor_run_tasks();
  }

  assert(core_battery_monitor_get_status() == CORE_BATTERY_NOT_READY);

  current_adc_val = adc++;
  core_battery_monitor_run_tasks();

  assert(core_battery_monitor_get_status() == CORE_BATTERY_CHARGE_LOW);

  // At the end of this the average of a buffer must be around 799
  for (int i = 0; i < 92; i++)
  {
    current_adc_val = adc++;
    core_battery_monitor_run_tasks();
  }

  current_adc_val = adc++;
  core_battery_monitor_run_tasks();
  assert(core_battery_monitor_get_status() == CORE_BATTERY_CHARGE_OK);
}
