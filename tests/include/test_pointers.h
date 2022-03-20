#include <assert.h>
#include <stdbool.h>
#include <stdio.h>

#include <api/prelude.h>
#include <helpers/system.h>
#include <log/prelude.h>

#if defined(_WIN32) || defined(_WIN64)
  #define POINTERS "examples\\pointers\\pointers.day"
  #define POINTERS_EXECUTABLE "tests\\out\\test_pointers.exe"
  #define POINTERS_OUTPUT_FILE "tests\\out\\output.txt"
#else
  #define POINTERS "examples/pointers/pointers.day"
  #define POINTERS_EXECUTABLE "tests/out/test_pointers"
  #define POINTERS_OUTPUT_FILE "tests/out/output.txt"
#endif


#define BUFFER_SIZE 1024

bool test_pointers();

bool test_pointers() {
  LOG_INFO("Running test [test_pointers] %s %s", POINTERS, POINTERS_EXECUTABLE);

  int error = daybreak_compile(POINTERS, POINTERS_EXECUTABLE);
  if (error != 0) {
    LOG_ERROR("Failed compiling pointers program via compiler API");
    return false;
  }

  FILE* output_file = fopen(POINTERS_OUTPUT_FILE, "w+");
  error = run_command(POINTERS_EXECUTABLE, output_file);
  fclose(output_file);

  output_file = fopen(POINTERS_OUTPUT_FILE, "r");
  
  char buffer[BUFFER_SIZE];
  memset(buffer, '\0', sizeof(char) * BUFFER_SIZE);
  fgets(buffer, BUFFER_SIZE, output_file);
  fclose(output_file);
  if (strcmp(buffer, POINTERS_EXECUTABLE) != 0) {
    LOG_ERROR("Failed to output '%s', got '%s'", POINTERS_EXECUTABLE, buffer);
    return false;
  }

  return true;
}
