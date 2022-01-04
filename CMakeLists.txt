cmake_minimum_required(VERSION 3.0.0)
set(CMAKE_C_COMPILER gcc)
set(CMAKE_CXX_COMPILER gcc)
project(DaybreakAll)

set(CMAKE_RUNTIME_OUTPUT_DIRECTORY ${CMAKE_BINARY_DIR}/bin)

add_subdirectory(src)