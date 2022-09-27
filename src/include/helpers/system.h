#pragma once

#include <errno.h>
#include <stdio.h>
#include <stdlib.h>
#include <sys/stat.h>

#include <log/prelude.h>

#define COMMAND_BUFFER_SIZE 1024
#ifndef MAX_PATH
  #define MAX_PATH 260
#endif

char* get_default_output_file();
char* get_standard_library_directory();
int run_command(const char*, FILE*);
int setup_language_directories();

int _create_subdir(const char*, const char*);

#if defined(_WIN32) || defined(_WIN64)
  #define STANDARD_PATH_PREFIX "C:"
  #define STANDARD_DIRECTORY "\\Program Files\\daybreak"
  #define OUTPUT_DIRECTORY "\\out\\"
  #define PACKAGE_DIRECTORY "\\packages\\"
  #define DEFAULT_EXECUTABLE "a.exe"
#else
  #define STANDARD_PATH_PREFIX (getenv("HOME"))
  #define STANDARD_DIRECTORY "/.daybreak"
  #define OUTPUT_DIRECTORY "/out/"
  #define PACKAGE_DIRECTORY "/packages/"
  #define DEFAULT_EXECUTABLE "a.out"
#endif

#define DEFAULT_SOURCE_OUTPUT "main.day.c"

inline char* get_standard_library_directory() {
  const char* daybreak_home_env = getenv("DAYBREAK_HOME");
  if (daybreak_home_env) {
    char* full_path = malloc(sizeof(char) * (strlen(daybreak_home_env) + 1));
    strcpy(full_path, daybreak_home_env);
    return full_path;
  }
  char* full_path = malloc(sizeof(char) * (strlen(STANDARD_PATH_PREFIX) + strlen(STANDARD_DIRECTORY) + 2));
  sprintf(full_path, "%s%s", STANDARD_PATH_PREFIX, STANDARD_DIRECTORY);
  return full_path;
}

int run_command(const char* command, FILE* output_stream) {
  FILE* command_stream = popen(command, "r");
  char buffer[COMMAND_BUFFER_SIZE];
  memset(buffer, '\0', sizeof(char) * COMMAND_BUFFER_SIZE);
  while (fgets(buffer, COMMAND_BUFFER_SIZE, command_stream)) {
    fputs(buffer, output_stream);
  }
  return pclose(command_stream);
}

int _create_dir(const char* directory) {
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

int _create_subdir(const char* directory, const char* subdirectory) {
  char* full_path = malloc(sizeof(char) * (strlen(directory) + strlen(subdirectory) + 2));
  sprintf(full_path, "%s/%s", directory, subdirectory);
  const int error = _create_dir(full_path);
  free(full_path);
  full_path = NULL;
  if (error != 0) {
    return error;
  }
  
  return 0;
}

char* get_default_output_file() {
  char* standard_library_directory = get_standard_library_directory();
  char* output_file_path = malloc(sizeof(char) * (strlen(standard_library_directory) + strlen(OUTPUT_DIRECTORY) + strlen(DEFAULT_EXECUTABLE) + 1));
  sprintf(output_file_path, "%s" OUTPUT_DIRECTORY DEFAULT_EXECUTABLE, standard_library_directory);
  free(standard_library_directory);
  return output_file_path;
}

int setup_language_directories() {
  char* standard_library_directory = get_standard_library_directory();
  
  int error = _create_dir(standard_library_directory);
  if (error != 0) {
    free(standard_library_directory);
    return errno;
  }

  error = _create_subdir(standard_library_directory, "bin");
  if (error != 0) {
    free(standard_library_directory);
    return error;
  }

  error = _create_subdir(standard_library_directory, "packages");
  if (error != 0) {
    free(standard_library_directory);
    return error;
  }

  error = _create_subdir(standard_library_directory, "out");
  if (error != 0) {
    free(standard_library_directory);
    return error;
  }

  free(standard_library_directory);
  return 0;
}
