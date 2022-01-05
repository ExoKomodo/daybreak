cmake_minimum_required(VERSION 3.0.0)
project(daybreak_test VERSION 0.1.0)

include_directories(../src/include)
link_directories(../src/lib)

add_executable(daybreak_test test_main.c)