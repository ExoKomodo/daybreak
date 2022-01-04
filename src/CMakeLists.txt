cmake_minimum_required(VERSION 3.0.0)
project(daybreak VERSION 0.1.0)

include_directories(include)
link_directories(lib)

add_executable(daybreak main.c)