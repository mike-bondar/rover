cmake_minimum_required(VERSION 3.20)

include(${CMAKE_CURRENT_LIST_DIR}/pico_sdk_import.cmake)

project(pico_rover C CXX ASM)

set(CMAKE_C_STANDARD 11)
set(CMAKE_CXX_STANDARD 17)

pico_sdk_init()

include(${CMAKE_CURRENT_LIST_DIR}/../cmake_libs.cmake)

add_executable(pico_rover)
target_link_libraries(pico_rover pico_stdlib core)
pico_add_extra_outputs(pico_rover)

add_subdirectory(${CMAKE_CURRENT_LIST_DIR}/src)

