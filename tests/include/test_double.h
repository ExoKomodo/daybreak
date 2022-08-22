#include <assert.h>
#include <stdbool.h>
#include <stdio.h>

#include <helpers/system.h>

#if defined(_WIN32) || defined(_WIN64)
  #define DOUBLE "examples\\double\\double.day"
  #define DOUBLE_EXECUTABLE "tests\\out\\test_double.exe"
  #define DOUBLE_OUTPUT_FILE "tests\\out\\output.txt"
#else
  #define DOUBLE "examples/double/double.day"
  #define DOUBLE_EXECUTABLE "tests/out/test_double"
  #define DOUBLE_OUTPUT_FILE "tests/out/output.txt"
#endif

#define BUFFER_SIZE 1024

#define DOUBLE_OUTPUT "Distance Squared: (0.000000, 1.200000) (3.400000, 5.600000) = 30.920000"

bool test_double();

bool test_double() {
  LOG_INFO("Running test [test_double] %s %s", DOUBLE, DOUBLE_EXECUTABLE);

  int error = daybreak_compile(
    (DaybreakArgs) {
      .source_file_path = DOUBLE,
      .output_file_path = DOUBLE_EXECUTABLE,
    }
  );
  if (error != 0) {
    LOG_ERROR("Failed compiling double program via compiler API");
    return false;
  }

  FILE* output_file = fopen(DOUBLE_OUTPUT_FILE, "w+");
  error = run_command(DOUBLE_EXECUTABLE, output_file);
  fclose(output_file);

  output_file = fopen(DOUBLE_OUTPUT_FILE, "r");
  
  char buffer[BUFFER_SIZE];
  memset(buffer, '\0', sizeof(char) * BUFFER_SIZE);
  fgets(buffer, BUFFER_SIZE, output_file);
  if (strcmp(buffer, DOUBLE_OUTPUT "\n") != 0) {
    fclose(output_file);
    LOG_ERROR("Failed to output '" DOUBLE_OUTPUT "', got '%s'", buffer);
    return false;
  }
  fclose(output_file);

  return true;
}
