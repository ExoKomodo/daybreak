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
char* system_get_standard_library_directory();
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

inline char* system_get_standard_library_directory() {
  const char* daybreak_home_env = getenv("DAYBREAK_HOME");
  if (daybreak_home_env) {
    char* full_path = malloc(sizeof(char) * (strlen(daybreak_home_env) + 1));
    strcpy(full_path, daybreak_home_env);
    return full_path;
  }
  char* full_path = malloc(sizeof(char) * (strlen(SYSTEM_STANDARD_PATH_PREFIX) + strlen(SYSTEM_STANDARD_DIRECTORY) + 2));
  sprintf(full_path, "%s%s", SYSTEM_STANDARD_PATH_PREFIX, SYSTEM_STANDARD_DIRECTORY);
  return full_path;
}

int system_run_command(const char* command, FILE* output_stream) {
  FILE* command_stream = popen(command, "r");
  char buffer[_SYSTEM_COMMAND_BUFFER_SIZE];
  memset(buffer, '\0', sizeof(char) * _SYSTEM_COMMAND_BUFFER_SIZE);
  while (fgets(buffer, _SYSTEM_COMMAND_BUFFER_SIZE, command_stream)) {
    fputs(buffer, output_stream);
  }
  return pclose(command_stream);
}

int _system_make_dir(const char* directory) {
#if defined(_WIN32) || defined(_WIN64)
  const int error = mkdir(directory);
#else
  const int error = mkdir(directory, 0777);
#endif
  if (error && errno != EEXIST) {
    LOG_ERROR("Failed to create directory %s: errno=%d", directory, errno);
    return error;
  }
  return 0;
}

int _system_make_subdir(const char* directory, const char* subdirectory) {
  char* full_path = malloc(sizeof(char) * (strlen(directory) + strlen(subdirectory) + 2));
  sprintf(full_path, "%s/%s", directory, subdirectory);
  const int error = _system_make_dir(full_path);
  free(full_path);
  full_path = NULL;
  if (error != 0) {
    return error;
  }
  
  return 0;
}

char* system_get_default_output_file() {
  char* standard_library_directory = system_get_standard_library_directory();
  char* output_file_path = malloc(sizeof(char) * (strlen(standard_library_directory) + strlen(SYSTEM_OUTPUT_DIRECTORY) + strlen(SYSTEM_DEFAULT_EXECUTABLE) + 1));
  sprintf(output_file_path, "%s" SYSTEM_OUTPUT_DIRECTORY SYSTEM_DEFAULT_EXECUTABLE, standard_library_directory);
  free(standard_library_directory);
  return output_file_path;
}

int system_setup_language_directories() {
  char* standard_library_directory = system_get_standard_library_directory();
  
  int error = _system_make_dir(standard_library_directory);
  if (error != 0) {
    free(standard_library_directory);
    return errno;
  }

  error = _system_make_subdir(standard_library_directory, "bin");
  if (error != 0) {
    free(standard_library_directory);
    return error;
  }

  error = _system_make_subdir(standard_library_directory, "packages");
  if (error != 0) {
    free(standard_library_directory);
    return error;
  }

  error = _system_make_subdir(standard_library_directory, "out");
  if (error != 0) {
    free(standard_library_directory);
    return error;
  }

  free(standard_library_directory);
  return 0;
}
