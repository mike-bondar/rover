add_subdirectory(${CMAKE_CURRENT_LIST_DIR}/drivers ${CMAKE_CURRENT_BINARY_DIR}/drivers)
add_subdirectory(${CMAKE_CURRENT_LIST_DIR}/core ${CMAKE_CURRENT_BINARY_DIR}/core)
add_subdirectory(${CMAKE_CURRENT_LIST_DIR}/commons ${CMAKE_CURRENT_BINARY_DIR}/commons)

message(STATUS "CMake libraries included successfully")