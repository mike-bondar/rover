#include "drivers/log.h"
#include "drivers/led.h"

#include "core/status_led.h"

void
core_init(void)
{
  core_status_led_init();
  core_status_led_success();
}

void
core_run_tasks(void)
{
  core_status_led_run_tasks();
}