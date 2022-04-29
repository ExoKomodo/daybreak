#include <assert.h>
#include <stdbool.h>
#include <stdio.h>

#include <api/prelude.h>
#include <helpers/system.h>
#include <log/prelude.h>

#if defined(_WIN32) || defined(_WIN64)
  #define MULTIPLE_IMPORTS "examples\\multiple_imports\\multiple_imports.day"
  #define MULTIPLE_IMPORTS_EXECUTABLE "tests\\out\\test_multiple_imports.exe"
  #define MULTIPLE_IMPORTS_OUTPUT_FILE "tests\\out\\output.txt"
#else
  #define MULTIPLE_IMPORTS "examples/multiple_imports/multiple_imports.day"
  #define MULTIPLE_IMPORTS_EXECUTABLE "tests/out/test_multiple_imports"
  #define MULTIPLE_IMPORTS_OUTPUT_FILE "tests/out/output.txt"
#endif

#define BUFFER_SIZE 1024

#define MULTIPLE_IMPORTS_OUTPUT "Multiple imports: 5"

bool test_multiple_imports();

bool test_multiple_imports() {
  LOG_INFO("Running test [test_multiple_imports] %s %s", MULTIPLE_IMPORTS, MULTIPLE_IMPORTS_EXECUTABLE);

  int error = daybreak_compile(
    (DaybreakArgs) {
      .source_file_path = MULTIPLE_IMPORTS,
      .output_file_path = MULTIPLE_IMPORTS_EXECUTABLE,
    }
  );
  if (error != 0) {
    LOG_ERROR("Failed compiling multiple_imports program via compiler API");
    return false;
  }

  FILE* output_file = fopen(MULTIPLE_IMPORTS_OUTPUT_FILE, "w+");
  error = run_command(MULTIPLE_IMPORTS_EXECUTABLE, output_file);
  fclose(output_file);

  output_file = fopen(MULTIPLE_IMPORTS_OUTPUT_FILE, "r");
  
  char buffer[BUFFER_SIZE];
  memset(buffer, '\0', sizeof(char) * BUFFER_SIZE);
  fgets(buffer, BUFFER_SIZE, output_file);
  if (strcmp(buffer, MULTIPLE_IMPORTS_OUTPUT "\n") != 0) {
    fclose(output_file);
    LOG_ERROR("Expected: " MULTIPLE_IMPORTS_OUTPUT ", got: %s", buffer);
    return false;
  }
  fclose(output_file);

  return true;
}
