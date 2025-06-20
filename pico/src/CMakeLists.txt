target_include_directories(pico_rover PRIVATE ${CMAKE_CURRENT_LIST_DIR}/include)
target_sources(pico_rover PRIVATE drivers.c main.c)