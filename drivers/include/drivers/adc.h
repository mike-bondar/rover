#pragma once

typedef enum {
  DRIVERS_ADC_BATTERY_MONITOR
} drivers_adc_t;

int drivers_adc_init(drivers_adc_t adc);

int drivers_adc_pull_latest(drivers_adc_t adc);
