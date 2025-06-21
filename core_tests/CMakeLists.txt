cmake_minimum_required(VERSION 3.20)

project(core_tests C CXX)

set(CMAKE_C_STANDARD 11)
set(CMAKE_CXX_STANDARD 17)

include(${CMAKE_CURRENT_LIST_DIR}/../cmake_libs.cmake)

enable_testing()

add_subdirectory(${CMAKE_CURRENT_LIST_DIR}/src)