#include <assert.h>
#include <stdbool.h>
#include <stdio.h>

#include <helpers/system.h>
#include <log/prelude.h>

#if defined(_WIN32) || defined(_WIN64)
  #define ENUM "examples\\enum\\enum.day"
  #define ENUM_EXECUTABLE "tests\\out\\test_enum.exe"
  #define ENUM_OUTPUT_FILE "tests\\out\\output.txt"
#else
  #define ENUM "examples/enum/enum.day"
  #define ENUM_EXECUTABLE "tests/out/test_enum"
  #define ENUM_OUTPUT_FILE "tests/out/output.txt"
#endif

#define BUFFER_SIZE 1024

#define ENUM_OUTPUT "Option: 100 Red: 0 Green: 1 Blue: 2"

bool test_enum();

bool test_enum() {
  LOG_INFO("Running test [test_enum] %s %s", ENUM, ENUM_EXECUTABLE);

  int error = daybreak_compile(
    (DaybreakArgs) {
      .source_file_path = ENUM,
      .output_file_path = ENUM_EXECUTABLE,
    }
  );
  if (error != 0) {
    LOG_ERROR("Failed compiling enum program via compiler API");
    return false;
  }

  FILE* output_file = fopen(ENUM_OUTPUT_FILE, "w+");
  error = run_command(ENUM_EXECUTABLE, output_file);
  fclose(output_file);

  output_file = fopen(ENUM_OUTPUT_FILE, "r");
  
  char buffer[BUFFER_SIZE];
  memset(buffer, '\0', sizeof(char) * BUFFER_SIZE);
  fgets(buffer, BUFFER_SIZE, output_file);
  if (strcmp(buffer, ENUM_OUTPUT "\n") != 0) {
    fclose(output_file);
    LOG_ERROR("Failed to output '" ENUM_OUTPUT "', got '%s'", buffer);
    return false;
  }
  fclose(output_file);

  return true;
}
