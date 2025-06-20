
add_library(core)

target_link_libraries(core PRIVATE drivers)

add_subdirectory(${CMAKE_CURRENT_LIST_DIR}/src)
target_include_directories(core PUBLIC ${CMAKE_CURRENT_LIST_DIR}/include)
