#pragma once

#define BATTERY_MONITOR_BUFFER_SIZE 16
#define BATTERY_MONITOR_CHARGE_OK_VALUE 800

typedef enum {
  CORE_BATTERY_NOT_READY,
  CORE_BATTERY_CHARGE_LOW,
  CORE_BATTERY_CHARGE_OK
} core_battery_monitor_status_t;

void
core_battery_monitor_run_tasks(void);

int
core_battery_monitor_init(void);

core_battery_monitor_status_t
core_battery_monitor_get_status(void);
