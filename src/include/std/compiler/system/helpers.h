#pragma once

#include <errno.h>
#include <stdio.h>
#include <stdlib.h>
#include <sys/stat.h>

#define _SYSTEM_COMMAND_BUFFER_SIZE 1024
#ifndef SYSTEM_MAX_PATH
  #define SYSTEM_MAX_PATH 260
#endif

char* system_get_default_output_file();
int system_run_command(const char*, FILE*);
int system_setup_language_directories();

int _system_make_subdir(const char*, const char*);

#if defined(_WIN32) || defined(_WIN64)
  #define SYSTEM_STANDARD_PATH_PREFIX "C:"
  #define SYSTEM_STANDARD_DIRECTORY "\\Program Files\\daybreak"
  #define SYSTEM_OUTPUT_DIRECTORY "\\out\\"
  #define SYSTEM_PACKAGE_DIRECTORY "\\packages\\"
  #define SYSTEM_DEFAULT_EXECUTABLE "a.exe"
#else
  #define SYSTEM_STANDARD_PATH_PREFIX (getenv("HOME"))
  #define SYSTEM_STANDARD_DIRECTORY "/.daybreak"
  #define SYSTEM_OUTPUT_DIRECTORY "/out/"
  #define SYSTEM_PACKAGE_DIRECTORY "/packages/"
  #define SYSTEM_DEFAULT_EXECUTABLE "a.out"
#endif

#define SYSTEM_DEFAULT_SOURCE_OUTPUT "main.day.c"

inline int _system_mkdir_common(const char* directory) {
  #if defined(_WIN32) || defined(_WIN64)
    return mkdir(directory);
  #else
    return mkdir(directory, 0777);
  #endif
}