#include "drivers/led.h"
#include "core/battery_monitor.h"

void
core_battery_status_led_init(void)
{
  drivers_led_init(DRIVERS_LED_BATTERY_CHARGE_LOW);
}

void
core_battery_status_led_run_tasks(void)
{
  switch(core_battery_monitor_get_status()) {
    case CORE_BATTERY_CHARGE_LOW:
      drivers_led_on(DRIVERS_LED_BATTERY_CHARGE_LOW);
      break;

    default:
      // Turn off the LED if the battery is not low
      drivers_led_off(DRIVERS_LED_BATTERY_CHARGE_LOW);
      break;
  }
}