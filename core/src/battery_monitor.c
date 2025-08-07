#include "drivers/adc.h"
#include "drivers/log.h"
#include "core/battery_monitor.h"
#include "core/battery_monitor_internal.h"
#include "string.h"

// Battery monitor private data

struct
{
  int data[BATTERY_MONITOR_BUFFER_SIZE];
  int head;
  int tail;
  int ready;
} buffer = { {0}, 0, 0, 0 };

static void
core_battery_monitor_clear_buffer(void)
{
  memset(buffer.data, 0, sizeof(buffer.data));
  buffer.head = 0;
  buffer.tail = 0;
  buffer.ready = 0;
}

static core_battery_monitor_status_t battery_status = CORE_BATTERY_NOT_READY;

static void
core_battery_monitor_pull_latest_data(void)
{
  int latest_value = drivers_adc_pull_latest(DRIVERS_ADC_BATTERY_MONITOR);

  // This means the ADC is not available for some reason
  if (latest_value <= 0)
  {
    core_battery_monitor_clear_buffer();
    return;
  }

  drivers_log_debug("buffer: head=%d, tail=%d, ready=%d, latest=%d", buffer.head, buffer.tail, buffer.ready, latest_value);

  buffer.data[buffer.head] = latest_value;

  int next_head = buffer.head + 1;
  if (next_head == BATTERY_MONITOR_BUFFER_SIZE)
  {
    // Buffer becomes ready once it's filled for the first time
    buffer.ready = 1;
    next_head = 0;
  }

  buffer.head = next_head;

  if (buffer.ready)
  {
    int next_tail = buffer.tail + 1;
    if (next_tail == BATTERY_MONITOR_BUFFER_SIZE)
    {
      next_tail = 0;
    }

    buffer.tail = next_tail;
  }
}

static void
core_battery_monitor_set_battery_status(void)
{
  if (!buffer.ready)
  {
    return;
  }

  int sum = 0;
  // Start position
  int pos = buffer.tail - 1;
  if (pos < 0)
  {
    pos = BATTERY_MONITOR_BUFFER_SIZE - 1;
  }

  for (int i = 0; i < BATTERY_MONITOR_BUFFER_SIZE; i++)
  {
    sum += buffer.data[pos];

    int next_pos = pos + 1;
    if (next_pos >= BATTERY_MONITOR_BUFFER_SIZE)
    {
      next_pos = 0;
    }

    pos = next_pos;
  } 

  int v = sum / BATTERY_MONITOR_BUFFER_SIZE;

  drivers_log_debug("buffer: avg=%d", v);

  if (v >= BATTERY_MONITOR_CHARGE_OK_VALUE)
  {
    battery_status = CORE_BATTERY_CHARGE_OK;
    return;
  }

  battery_status = CORE_BATTERY_CHARGE_LOW;
}

int
core_battery_monitor_init(void)
{
  drivers_adc_init(DRIVERS_ADC_BATTERY_MONITOR);
  core_battery_monitor_clear_buffer(); 
}


core_battery_monitor_status_t
core_battery_monitor_get_status(void)
{
  return battery_status;
}

void
core_battery_monitor_run_tasks(void)
{
  core_battery_monitor_pull_latest_data();
  core_battery_monitor_set_battery_status();
}
