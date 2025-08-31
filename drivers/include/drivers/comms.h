#pragma once
#include <cstddef>

typedef enum {
  COMMS_COMMAND_NONE, // Returned when no command's been received since the last call
  COMMS_COMMAND_PING, // Ping command to check connectivity
  COMMS_COMMAND_STATUS // Status command to request the current status
} comms_command_t;

void
drivers_comms_init(void);

comms_command_t
drivers_comms_receive_command(void);

void
drivers_commsn_send_data(const char *data, size_t len);