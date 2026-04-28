cmake_minimum_required(VERSION 3.10)
project(hello_window VERSION 1.0.0)

find_package(glfw3 3.3 REQUIRED)

add_executable(hello_window src/main.cpp src/config.h)

target_include_directories(hello_window PRIVATE lib)
target_link_libraries(hello_window PRIVATE glfw)