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
  -Wnull-dereference
  -Wdouble-promotion
  -Wno-endif-labels
)

if (CMAKE_C_COMPILER_ID STREQUAL "GNU")
  add_compile_options(
    -Wduplicated-cond
    -Wduplicated-branches
    -Wlogical-op
  )
elseif (CMAKE_C_COMPILER_ID MATCHES "Clang")
  add_compile_options(
    -Wno-gnu-zero-variadic-macro-arguments
    -Wnewline-eof
    -Wno-static-in-inline
  )
endif()

add_subdirectory(src)
add_subdirectory(tests)
