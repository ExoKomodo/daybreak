#pragma once

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include <helpers/system.h>
#include <log/prelude.h>
#include <macros/helpers.h>

#define FLAGS ""
#define DEFAULT_COMPILE_COMMAND_FORMAT "cc -o %s %s"

int compile_c_code(const char*, const char*);

int compile_c_code(
  const char* source_file_path,
  const char* executable_path
) {
  char* command = malloc(
    sizeof(char) *
    (
      strlen(DEFAULT_COMPILE_COMMAND_FORMAT) +
      strlen(executable_path) +
      strlen(source_file_path) +
      1
    )
  );
  sprintf(
    command,
    DEFAULT_COMPILE_COMMAND_FORMAT,
    executable_path,
    source_file_path
  );

  LOG_DEBUG("Running compiler command: %s", command);

  int error = run_command(command, stdout);
  free(command);
  command = NULL;
  if (error != 0) {
    LOG_ERROR("Failed to compile C code: %d", error);
    return error;
  }
  return 0;
}
