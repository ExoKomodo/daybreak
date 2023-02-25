#include <assert.h>
#include <stdbool.h>
#include <stdio.h>

#include <helpers/system.h>
#include <log/prelude.h>

#if defined(_WIN32) || defined(_WIN64)
  #define ARRAY "examples\\array\\array.day"
  #define ARRAY_EXECUTABLE "tests\\out\\test_array.exe"
  #define ARRAY_OUTPUT_FILE "tests\\out\\output.txt"
#else
  #define ARRAY "examples/array/array.day"
  #define ARRAY_EXECUTABLE "tests/out/test_array"
  #define ARRAY_OUTPUT_FILE "tests/out/output.txt"
#endif

#define ARRAY_OUTPUT "length of primes: 8"

#define BUFFER_SIZE 1024

bool test_array();

bool test_array() {
  LOG_INFO("Running test [test_array] %s %s", ARRAY, ARRAY_EXECUTABLE);

  int error = daybreak_compile(
    (DaybreakArgs) {
      .source_file_path = ARRAY,
      .output_file_path = ARRAY_EXECUTABLE,
    }
  );
  if (error != 0) {
    LOG_ERROR("Failed compiling array program via compiler API");
    return false;
  }

  FILE* output_file = fopen(ARRAY_OUTPUT_FILE, "w+");
  error = run_command(ARRAY_EXECUTABLE, output_file);
  fclose(output_file);

  output_file = fopen(ARRAY_OUTPUT_FILE, "r");
  
  char buffer[BUFFER_SIZE];
  memset(buffer, '\0', sizeof(char) * BUFFER_SIZE);
  fgets(buffer, BUFFER_SIZE, output_file);
  fclose(output_file);
  if (strcmp(buffer, ARRAY_OUTPUT "\n") != 0) {
    LOG_ERROR("Failed to output '%s', got '%s'", ARRAY_OUTPUT, buffer);
    return false;
  }
  return true;
}
