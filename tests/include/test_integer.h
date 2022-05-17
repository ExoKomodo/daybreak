#include <assert.h>
#include <stdbool.h>
#include <stdio.h>

#include <helpers/system.h>
#include <log/prelude.h>

#if defined(_WIN32) || defined(_WIN64)
  #define INTEGER "examples\\integer\\integer.day"
  #define INTEGER_EXECUTABLE "tests\\out\\test_integer.exe"
  #define INTEGER_OUTPUT_FILE "tests\\out\\output.txt"
#else
  #define INTEGER "examples/integer/integer.day"
  #define INTEGER_EXECUTABLE "tests/out/test_integer"
  #define INTEGER_OUTPUT_FILE "tests/out/output.txt"
#endif

#define BUFFER_SIZE 1024

#define INTEGER_OUTPUT "Integer: 420"

bool test_integer();

bool test_integer() {
  LOG_INFO("Running test [test_integer] %s %s", INTEGER, INTEGER_EXECUTABLE);

  int error = daybreak_compile(
    (DaybreakArgs) {
      .source_file_path = INTEGER,
      .output_file_path = INTEGER_EXECUTABLE,
    }
  );
  if (error != 0) {
    LOG_ERROR("Failed compiling integer program via compiler API");
    return false;
  }

  FILE* output_file = fopen(INTEGER_OUTPUT_FILE, "w+");
  error = run_command(INTEGER_EXECUTABLE, output_file);
  fclose(output_file);

  output_file = fopen(INTEGER_OUTPUT_FILE, "r");
  
  char buffer[BUFFER_SIZE];
  memset(buffer, '\0', sizeof(char) * BUFFER_SIZE);
  fgets(buffer, BUFFER_SIZE, output_file);
  if (strcmp(buffer, INTEGER_OUTPUT "\n") != 0) {
    fclose(output_file);
    LOG_ERROR("Failed to output '" INTEGER_OUTPUT "', got '%s'", buffer);
    return false;
  }
  fclose(output_file);

  return true;
}
