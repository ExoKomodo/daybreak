#pragma once

#include <stdio.h>

#include <log/prelude.h>

#define COMMAND_BUFFER_SIZE 1024

int run_command(const char*, FILE*);

int run_command(const char* command, FILE* output_stream) {
  FILE* command_stream = popen(command, "r");
  char buffer[COMMAND_BUFFER_SIZE];
  memset(buffer, '\0', sizeof(char) * COMMAND_BUFFER_SIZE);
  while (fgets(buffer, COMMAND_BUFFER_SIZE, command_stream)) {
    fputs(buffer, output_stream);
  }
  return pclose(command_stream);
}
