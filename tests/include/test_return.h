#include <assert.h>
#include <stdbool.h>
#include <stdio.h>

#include <helpers/system.h>
#include <log/prelude.h>

#if defined(_WIN32) || defined(_WIN64)
  #define RETURN "examples\\return\\return.day"
  #define RETURN_EXECUTABLE "tests\\out\\test_return.exe"
  #define RETURN_OUTPUT_FILE "tests\\out\\output.txt"
#else
  #define RETURN "examples/return/return.day"
  #define RETURN_EXECUTABLE "tests/out/test_return"
  #define RETURN_OUTPUT_FILE "tests/out/output.txt"
#endif

#define BUFFER_SIZE 1024

#define RETURN_OUTPUT "x: 0"

bool test_return();

bool test_return() {
  LOG_INFO("Running test [test_return] %s %s", RETURN, RETURN_EXECUTABLE);

  int error = daybreak_compile(
    (DaybreakArgs) {
      .source_file_path = RETURN,
      .output_file_path = RETURN_EXECUTABLE,
    }
  );
  if (error != 0) {
    LOG_ERROR("Failed compiling return program via compiler API");
    return false;
  }

  FILE* output_file = fopen(RETURN_OUTPUT_FILE, "w+");
  error = run_command(RETURN_EXECUTABLE, output_file);
  fclose(output_file);

  output_file = fopen(RETURN_OUTPUT_FILE, "r");
  
  char buffer[BUFFER_SIZE];
  memset(buffer, '\0', sizeof(char) * BUFFER_SIZE);
  fgets(buffer, BUFFER_SIZE, output_file);
  fclose(output_file);
  if (strcmp(buffer, RETURN_OUTPUT "\n") != 0) {
    LOG_ERROR("Failed to output '" RETURN_OUTPUT "', got '%s'", buffer);
    return false;
  }

  return true;
}
