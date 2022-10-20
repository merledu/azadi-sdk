cmake_minimum_required(VERSION 3.20)
project(AzadiSDK)


add_executable(${PROJECT_NAME} softwares/gpio_test/gpio_test.c)

include_directories(bsp/include)
add_subdirectory(bsp/src)
add_subdirectory(bsp/azadi)