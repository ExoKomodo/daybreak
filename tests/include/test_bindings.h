#include <assert.h>
#include <stdbool.h>
#include <stdio.h>

#include <helpers/system.h>
#include <log/prelude.h>

#if defined(_WIN32) || defined(_WIN64)
  #define BINDINGS "examples\\bindings\\bindings.day"
  #define BINDINGS_EXECUTABLE "tests\\out\\test_bindings.exe"
  #define BINDINGS_OUTPUT_FILE "tests\\out\\output.txt"
#else
  #define BINDINGS "examples/bindings/bindings.day"
  #define BINDINGS_EXECUTABLE "tests/out/test_bindings"
  #define BINDINGS_OUTPUT_FILE "tests/out/output.txt"
#endif

#define BINDINGS_OUTPUT "x = 10, y = 20"

#define BUFFER_SIZE 1024

bool test_bindings();

bool test_bindings() {
  LOG_INFO("Running test [test_bindings] %s %s", BINDINGS, BINDINGS_EXECUTABLE);

  int error = daybreak_compile(
    (DaybreakArgs) {
      .source_file_path = BINDINGS,
      .output_file_path = BINDINGS_EXECUTABLE,
    }
  );
  if (error != 0) {
    LOG_ERROR("Failed compiling bindings program via compiler API");
    return false;
  }

  FILE* output_file = fopen(BINDINGS_OUTPUT_FILE, "w+");
  error = run_command(BINDINGS_EXECUTABLE, output_file);
  fclose(output_file);

  output_file = fopen(BINDINGS_OUTPUT_FILE, "r");
  
  char buffer[BUFFER_SIZE];
  memset(buffer, '\0', sizeof(char) * BUFFER_SIZE);
  fgets(buffer, BUFFER_SIZE, output_file);
  fclose(output_file);
  if (strcmp(buffer, BINDINGS_OUTPUT "\n") != 0) {
    LOG_ERROR("Failed to output '%s', got '%s'", BINDINGS_OUTPUT, buffer);
    return false;
  }
  return true;
}
