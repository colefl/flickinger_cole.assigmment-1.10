cmake_minimum_required(VERSION 3.10)
project(hello_window VERSION 1.0.0)

find_package(OpenGL REQUIRED)

add_executable(hello_window
 src/main.cpp 
 src/config.h 
 src/glad.c
 src/triangle_mesh.cpp
 src/triangle_mesh.h
)

find_package(glfw3 3.3 REQUIRED)

target_include_directories(hello_window PRIVATE dependencies)
target_link_libraries(hello_window glfw OpenGL::GL)
