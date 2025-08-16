#include "drivers/log.h"
#include "drivers/led.h"
#include "core/status_led.h"
#include "core/battery_monitor.h"
#include "core/battery_status_led.h"

void
core_init(void)
{
  core_status_led_init();
  core_battery_monitor_init();
  core_battery_status_led_init();

  core_status_led_success();
}

void
core_run_tasks(void)
{
  core_battery_monitor_run_tasks();
  core_status_led_run_tasks();
  core_battery_status_led_run_tasks();
}
