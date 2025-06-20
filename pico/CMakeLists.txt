cmake_minimum_required(VERSION 3.30)
project(pico_rover C CXX ASM)

include(${CMAKE_CURRENT_LIST_DIR}/../cmake_libs.cmake)

add_executable(pico_rover)
target_link_libraries(pico_rover PRIVATE core)

add_subdirectory(${CMAKE_CURRENT_LIST_DIR}/src ${CMAKE_CURRENT_BINARY_DIR}/src)
