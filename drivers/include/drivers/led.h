#pragma once

typedef enum {
  DRIVERS_LED_SUCCESS
} drivers_led_t;

int
drivers_led_init(drivers_led_t led);

void
drivers_led_on(drivers_led_t led);

void
drivers_led_off(drivers_led_t led);

void
drivers_led_toggle(drivers_led_t led);