#pragma once

#define CORE_STATUS_LED_TASK_INTERVAL_MS 1000
#define CORE_STATUS_LED_SUCCESS_BLINK_COUNT 3
#define CORE_STATUS_LED_SUCCESS_DURATION_MS 100

void
core_status_led_run_tasks(void);

int
core_status_led_success(void);