#include <assert.h>
#include <stdbool.h>
#include <stdio.h>

#include <api/prelude.h>
#include <helpers/system.h>
#include <log/prelude.h>

#if defined(_WIN32) || defined(_WIN64)
  #define MATCH "examples\\match\\match.day"
  #define MATCH_EXECUTABLE "tests\\out\\test_match.exe"
  #define MATCH_OUTPUT_FILE "tests\\out\\output.txt"
#else
  #define MATCH "examples/match/match.day"
  #define MATCH_EXECUTABLE "tests/out/test_match"
  #define MATCH_OUTPUT_FILE "tests/out/output.txt"
#endif

#define MATCH_OUTPUT "x was 10"

#define BUFFER_SIZE 1024

bool test_match();

bool test_match() {
  LOG_INFO("Running test [test_match] %s %s", MATCH, MATCH_EXECUTABLE);

  int error = daybreak_compile(
    (DaybreakArgs) {
      .source_file_path = MATCH,
      .output_file_path = MATCH_EXECUTABLE,
    }
  );
  if (error != 0) {
    LOG_ERROR("Failed compiling match program via compiler API");
    return false;
  }

  FILE* output_file = fopen(MATCH_OUTPUT_FILE, "w+");
  error = run_command(MATCH_EXECUTABLE, output_file);
  fclose(output_file);

  output_file = fopen(MATCH_OUTPUT_FILE, "r");
  
  char buffer[BUFFER_SIZE];
  memset(buffer, '\0', sizeof(char) * BUFFER_SIZE);
  fgets(buffer, BUFFER_SIZE, output_file);
  fclose(output_file);
  if (strcmp(buffer, MATCH_OUTPUT "\n") != 0) {
    LOG_ERROR("Failed to output '%s', got '%s'", MATCH_OUTPUT, buffer);
    return false;
  }

  return true;
}
