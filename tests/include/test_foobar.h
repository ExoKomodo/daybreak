#include <assert.h>
#include <stdbool.h>
#include <stdio.h>

#include <helpers/system.h>
#include <log/prelude.h>

#if defined(_WIN32) || defined(_WIN64)
  #define FOOBAR "examples\\foobar\\foobar.day"
  #define FOOBAR_EXECUTABLE "tests\\out\\test_foobar.exe"
  #define FOOBAR_OUTPUT_FILE "tests\\out\\output.txt"
#else
  #define FOOBAR "examples/foobar/foobar.day"
  #define FOOBAR_EXECUTABLE "tests/out/test_foobar"
  #define FOOBAR_OUTPUT_FILE "tests/out/output.txt"
#endif

#define BUFFER_SIZE 1024

bool test_foobar();

bool test_foobar() {
  LOG_INFO("Running test [test_foobar] %s %s", FOOBAR, FOOBAR_EXECUTABLE);

  int error = daybreak_compile(
    (DaybreakArgs) {
      .source_file_path = FOOBAR,
      .output_file_path = FOOBAR_EXECUTABLE,
    }
  );
  if (error != 0) {
    LOG_ERROR("Failed compiling foobar program via compiler API");
    return false;
  }

  FILE* output_file = fopen(FOOBAR_OUTPUT_FILE, "w+");
  error = run_command(FOOBAR_EXECUTABLE, output_file);
  fclose(output_file);

  output_file = fopen(FOOBAR_OUTPUT_FILE, "r");
  
  char buffer[BUFFER_SIZE];
  memset(buffer, '\0', sizeof(char) * BUFFER_SIZE);
  fgets(buffer, BUFFER_SIZE, output_file);
  if (strcmp(buffer, "Foo: Hello!\n") != 0) {
    fclose(output_file);
    LOG_ERROR("Failed to output 'Foo: Hello!', got '%s'", buffer);
    return false;
  }
  fgets(buffer, BUFFER_SIZE, output_file);
  if (strcmp(buffer, "Bar: 2 Hello again!!\n") != 0) {
    fclose(output_file);
    LOG_ERROR("Failed to output 'Bar: 2 Hello again!!', got '%s'", buffer);
    return false;
  }
  fclose(output_file);

  return true;
}
