#include <assert.h>
#include <stdbool.h>
#include <stdio.h>

#include <api/prelude.h>
#include <helpers/system.h>
#include <log/prelude.h>

#if defined(_WIN32) || defined(_WIN64)
  #define VARIABLES "examples\\variables\\variables.day"
  #define VARIABLES_EXECUTABLE "out\\test_variables.exe"
  #define VARIABLES_OUTPUT_FILE "out\\output.txt"
#else
  #define VARIABLES "examples/variables/variables.day"
  #define VARIABLES_EXECUTABLE "out/test_variables"
  #define VARIABLES_OUTPUT_FILE "out/output.txt"
#endif


#define BUFFER_SIZE 1024

bool test_variables();

bool test_variables() {
  LOG_INFO("Running test [test_variables] %s %s", VARIABLES, VARIABLES_EXECUTABLE);

  int error = daybreak_compile(VARIABLES, VARIABLES_EXECUTABLE);
  if (error != 0) {
    LOG_ERROR("Failed compiling variables program via compiler API");
    return false;
  }

  FILE* output_file = fopen(VARIABLES_OUTPUT_FILE, "w+");
  error = run_command(VARIABLES_EXECUTABLE, output_file);
  fclose(output_file);

  output_file = fopen(VARIABLES_OUTPUT_FILE, "r");
  
  char buffer[BUFFER_SIZE];
  memset(buffer, '\0', sizeof(char) * BUFFER_SIZE);
  fgets(buffer, BUFFER_SIZE, output_file);
  fclose(output_file);
  if (strcmp(buffer, "x = 10, y = 51\n") != 0) {
    LOG_ERROR("Failed to output \"x = 10, y = 51\"");
    return false;
  }
  return true;
}
