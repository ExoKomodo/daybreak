#include <assert.h>
#include <stdbool.h>
#include <stdio.h>

#include <api/prelude.h>
#include <helpers/system.h>
#include <log/prelude.h>

#if defined(_WIN32) || defined(_WIN64)
  #define TYPES "examples\\types\\types.day"
  #define TYPES_EXECUTABLE "out\\test_types.exe"
  #define TYPES_OUTPUT_FILE "out\\output.txt"
#else
  #define TYPES "examples/types/types.day"
  #define TYPES_EXECUTABLE "out/test_types"
  #define TYPES_OUTPUT_FILE "out/output.txt"
#endif

#define TYPES_OUTPUT "Foo: 1 2, Bar: 3"

#define BUFFER_SIZE 1024

bool test_types();

bool test_types() {
  LOG_INFO("Running test [test_types] %s %s", TYPES, TYPES_EXECUTABLE);

  int error = daybreak_compile(TYPES, TYPES_EXECUTABLE);
  if (error != 0) {
    LOG_ERROR("Failed compiling hello world program via compiler API");
    return false;
  }

  FILE* output_file = fopen(TYPES_OUTPUT_FILE, "w+");
  error = run_command(TYPES_EXECUTABLE, output_file);
  fclose(output_file);

  output_file = fopen(TYPES_OUTPUT_FILE, "r");
  
  char buffer[BUFFER_SIZE];
  memset(buffer, '\0', sizeof(char) * BUFFER_SIZE);
  while (fgets(buffer, BUFFER_SIZE, output_file)) {
    if (strcmp(buffer, TYPES_OUTPUT "\n") != 0) {
      fclose(output_file);
      LOG_ERROR("Failed to output '%s', got '%s'", TYPES_OUTPUT, buffer);
      return false;
    }
  }
  fclose(output_file);

  return true;
}
