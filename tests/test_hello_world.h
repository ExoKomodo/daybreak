#include <assert.h>
#include <stdbool.h>
#include <stdio.h>

#include <api/prelude.h>
#include <helpers/system.h>
#include <log/prelude.h>

#if defined(_WIN32) || defined(_WIN64)
  #define HELLO_WORLD "examples\\hello\\hello.day"
  #define EXECUTABLE "out\\test_hello_world.exe"
  #define OUTPUT_FILE "out\\output.txt"
#else
  #define HELLO_WORLD "examples/hello/hello.day"
  #define EXECUTABLE "out/test_hello_world"
  #define OUTPUT_FILE "out/output.txt"
#endif


#define BUFFER_SIZE 1024

bool test_hello_world();

bool test_hello_world() {
  LOG_INFO("Running test [test_hello_world] %s %s", HELLO_WORLD, EXECUTABLE);

  int error = daybreak_compile(HELLO_WORLD, EXECUTABLE);
  if (error != 0) {
    LOG_ERROR("Failed compilation hello world program via compiler API");
    return false;
  }

  FILE* output_file = fopen(OUTPUT_FILE, "w+");
  error = run_command(EXECUTABLE, output_file);
  fclose(output_file);

  output_file = fopen(OUTPUT_FILE, "r");
  
  char buffer[BUFFER_SIZE];
  memset(buffer, '\0', sizeof(char) * BUFFER_SIZE);
  while (fgets(buffer, BUFFER_SIZE, output_file)) {
    if (strcmp(buffer, "Hello world\n") != 0) {
      fclose(output_file);
      LOG_ERROR("Failed to output \"Hello world\"");
      return false;
    }
  }
  fclose(output_file);

  return true;
}
