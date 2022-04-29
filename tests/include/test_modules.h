#include <assert.h>
#include <stdbool.h>
#include <stdio.h>

#include <api/prelude.h>
#include <helpers/system.h>
#include <log/prelude.h>

#if defined(_WIN32) || defined(_WIN64)
  #define MODULES "examples\\modules\\modules.day"
  #define MODULES_EXECUTABLE "tests\\out\\test_modules.exe"
  #define MODULES_OUTPUT_FILE "tests\\out\\output.txt"
#else
  #define MODULES "examples/modules/modules.day"
  #define MODULES_EXECUTABLE "tests/out/test_modules"
  #define MODULES_OUTPUT_FILE "tests/out/output.txt"
#endif

#define BUFFER_SIZE 1024

bool test_modules();

bool test_modules() {
  LOG_INFO("Running test [test_modules] %s %s", MODULES, MODULES_EXECUTABLE);

  int error = daybreak_compile(
    (DaybreakArgs) {
      .source_file_path = MODULES,
      .output_file_path = MODULES_EXECUTABLE,
    }
  );
  if (error != 0) {
    LOG_ERROR("Failed compiling modules program via compiler API");
    return false;
  }

  FILE* output_file = fopen(MODULES_OUTPUT_FILE, "w+");
  error = run_command(MODULES_EXECUTABLE, output_file);
  fclose(output_file);

  output_file = fopen(MODULES_OUTPUT_FILE, "r");
  
  char buffer[BUFFER_SIZE];
  memset(buffer, '\0', sizeof(char) * BUFFER_SIZE);
  fgets(buffer, BUFFER_SIZE, output_file);
  if (strcmp(buffer, "a: 1, 'Hello world' length: 11\n") != 0) {
    fclose(output_file);
    LOG_ERROR("Failed to output 'a: 1, 'Hello world' length: 11', got '%s'", buffer);
    return false;
  }
  fgets(buffer, BUFFER_SIZE, output_file);
  if (strcmp(buffer, "a: 0, 'Hello world' length: 11\n") != 0) {
    fclose(output_file);
    LOG_ERROR("Failed to output 'a: 0, 'Hello world' length: 11', got '%s'", buffer);
    return false;
  }
  fclose(output_file);

  return true;
}
