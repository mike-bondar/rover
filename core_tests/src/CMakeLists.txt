function(add_core_test test_name)
  add_executable(${test_name} ${test_name}.c)
  target_link_libraries(${test_name} core drivers commons)
  add_test(NAME ${test_name} COMMAND ${test_name})
endfunction()

add_core_test(status_led_success_test)
add_core_test(battery_monitor_test)
