cmake_minimum_required(VERSION 3.0.0)
project(DaybreakAll)

set(CMAKE_RUNTIME_OUTPUT_DIRECTORY ${CMAKE_BINARY_DIR}/bin)
set(CMAKE_C_STANDARD 11)
add_compile_options(
  -Werror
  -Wall
  -Wextra
  -Wshadow
  -pedantic
  -Wconversion
  -Wsign-conversion
  -Wmisleading-indentation
  -Wduplicated-cond
  -Wduplicated-branches
  -Wlogical-op
  -Wnull-dereference
  -Wdouble-promotion
  -Wformat=2
)

add_subdirectory(src)
add_subdirectory(tests)