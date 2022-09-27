#include <assert.h>
#include <stdbool.h>
#include <stdio.h>

#include <helpers/system.h>

#if defined(_WIN32) || defined(_WIN64)
  #define NEW "examples\\new\\new.day"
  #define NEW_EXECUTABLE "tests\\out\\test_new.exe"
  #define NEW_OUTPUT_FILE "tests\\out\\output.txt"
#else
  #define NEW "examples/new/new.day"
  #define NEW_EXECUTABLE "tests/out/test_new"
  #define NEW_OUTPUT_FILE "tests/out/output.txt"
#endif

#define BUFFER_SIZE 1024

#define NEW_OUTPUT "a: 1 b: foo"

bool test_new();

bool test_new() {
  LOG_INFO("Running test [test_new] %s %s", NEW, NEW_EXECUTABLE);

  int error = daybreak_compile(
    (DaybreakArgs) {
      .source_file_path = NEW,
      .output_file_path = NEW_EXECUTABLE,
    }
  );
  if (error != 0) {
    LOG_ERROR("Failed compiling new program via compiler API");
    return false;
  }

  FILE* output_file = fopen(NEW_OUTPUT_FILE, "w+");
  error = run_command(NEW_EXECUTABLE, output_file);
  fclose(output_file);

  output_file = fopen(NEW_OUTPUT_FILE, "r");
  
  char buffer[BUFFER_SIZE];
  memset(buffer, '\0', sizeof(char) * BUFFER_SIZE);
  fgets(buffer, BUFFER_SIZE, output_file);
  fclose(output_file);
  if (strcmp(buffer, NEW_OUTPUT "\n") != 0) {
    LOG_ERROR("Failed to output '" NEW_OUTPUT "', got '%s'", buffer);
    return false;
  }

  return true;
}
