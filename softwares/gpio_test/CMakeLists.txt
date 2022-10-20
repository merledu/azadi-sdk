add_executable(app gpio_test.c)

target_include_directories(app PUBLIC bsp/include)

target_link_libraries(app PRIVATE bsp)