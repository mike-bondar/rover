#pragma once

typedef enum {
  DRIVERS_LED_SUCCESS,
  DRIVERS_LED_ERROR,
  DRIVERS_LED_WARNING
} DRIVERS_LED;

void
drivers_led_on(DRIVERS_LED led);

void
drivers_led_off(DRIVERS_LED led);

void
drivers_led_toggle(DRIVERS_LED led);