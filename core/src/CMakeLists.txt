target_sources(core PRIVATE core.c status_led.c battery_monitor.c battery_status.c)
target_include_directories(core PRIVATE ${CMAKE_CURRENT_LIST_DIR}/include)
