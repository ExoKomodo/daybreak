#pragma once

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include <helpers/system.h>
#include <log/prelude.h>
#include <macros/helpers.h>

#define CC_FLAGS "" \
  "-O2 " \
  "-foptimize-sibling-calls " \
  "-Werror " \
  "-Wall " \
  "-Wextra " \
  "-Wshadow " \
  "-pedantic " \
  "-Wsign-conversion " \
  "-Wnull-dereference " \
  "-Wdouble-promotion " \
  "-Wno-endif-labels "

#define CC_COMPILE_COMMAND_FORMAT "cc %s -o \"%s\" \"%s\""

int compile_c_code(const char*, const char*);
char* _build_command(const char*, const char*);

int compile_c_code(
  const char* source_file_path,
  const char* executable_path
) {
  char* command = _build_command(source_file_path, executable_path);

  LOG_DEBUG("Running compiler command: %s", command);

  const int error = run_command(command, stdout);
  free(command);
  command = NULL;
  if (error != 0) {
    LOG_ERROR("Failed to compile C code: %d", error);
    return error;
  }
  return 0;
}

char* _build_command(const char* source_file_path, const char* executable_path) {
  char* command = malloc(
    sizeof(char) *
    (
      strlen(CC_COMPILE_COMMAND_FORMAT) +
      strlen(CC_FLAGS) +
      strlen(executable_path) +
      strlen(source_file_path) +
      1
    )
  );
  sprintf(
    command,
    CC_COMPILE_COMMAND_FORMAT,
    CC_FLAGS,
    executable_path,
    source_file_path
  );
  return command;
}
