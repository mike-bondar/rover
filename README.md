# Project directory structure

- **drivers/**
Hardware abstraction layer. Must be implemented by a specific board

# IDEAS

1. Battery charge tracker with LED indicating a low battery charge
2. Status LED that blinks every second indicating the rover is running fine
3. Error LED blinking three times every second in case of an error
4. MQTT message exchange
5. Power from 4 AAAA batteries ? Do they fit into battery compartment of a rover?
6. Control with a computer keyboard. W, S to move back, A and D for turns. Moving and turning only while the button is pressed.
7. Have two parralel builds. On for PICO and one for the host machine to run tests