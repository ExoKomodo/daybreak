#include <assert.h>
#include <stdbool.h>
#include <stdio.h>

#include <std/compiler/system/helpers.h>
#include <log/prelude.h>

#if defined(_WIN32) || defined(_WIN64)
  #define SHEBANG "examples\\shebang\\shebang.day"
  #define SHEBANG_EXECUTABLE "tests\\out\\test_shebang.exe"
  #define SHEBANG_OUTPUT_FILE "tests\\out\\output.txt"
#else
  #define SHEBANG "examples/shebang/shebang.day"
  #define SHEBANG_EXECUTABLE "tests/out/test_shebang"
  #define SHEBANG_OUTPUT_FILE "tests/out/output.txt"
#endif

#define BUFFER_SIZE 1024

bool test_shebang();
bool _test_shebang(const char*, const bool);

bool test_shebang() {
  LOG_INFO("Running test [test_shebang] %s %s", SHEBANG, SHEBANG_EXECUTABLE);
  return (
    _test_shebang(SHEBANG_EXECUTABLE, false) &&
    _test_shebang(SHEBANG, true)
  );
}

bool _test_shebang(const char* command, const bool include_greeting) {
  int error = daybreak_compile(
    (DaybreakArgs) {
      .source_file_path = SHEBANG,
      .output_file_path = SHEBANG_EXECUTABLE,
    }
  );
  if (error != 0) {
    LOG_ERROR("Failed compiling shebang program via compiler API");
    return false;
  }

  FILE* output_file = fopen(SHEBANG_OUTPUT_FILE, "w+");
  error = run_command(command, output_file);
  fclose(output_file);

  output_file = fopen(SHEBANG_OUTPUT_FILE, "r");
  
  char buffer[BUFFER_SIZE];
  memset(buffer, '\0', sizeof(char) * BUFFER_SIZE);
  if (include_greeting) {
    fgets(buffer, BUFFER_SIZE, output_file);
    if (strcmp(buffer, ANSI_FOREGROUND_YELLOW "#####################################" ANSI_RESET "\n") != 0) {
      fclose(output_file);
      LOG_ERROR("Failed to get greeting, got\n'%s'", buffer);
      return false;  
    }
    fgets(buffer, BUFFER_SIZE, output_file);
    if (strcmp(buffer, ANSI_FOREGROUND_YELLOW "# Welcome to the Daybreak compiler! #" ANSI_RESET "\n") != 0) {
      fclose(output_file);
      LOG_ERROR("Failed to get greeting, got\n'%s'", buffer);
      return false;  
    }
    fgets(buffer, BUFFER_SIZE, output_file);
    if (strcmp(buffer, ANSI_FOREGROUND_YELLOW "#####################################" ANSI_RESET "\n") != 0) {
      fclose(output_file);
      LOG_ERROR("Failed to get greeting, got\n'%s'", buffer);
      return false;  
    }
    fgets(buffer, BUFFER_SIZE, output_file); // Skip line as it often changes
  }

  fgets(buffer, BUFFER_SIZE, output_file);
  if (strcmp(buffer, "Running with shebang\n") != 0) {
    fclose(output_file);
    LOG_ERROR("Failed to output\n'%s', got\n'%s'", "Running with shebang", buffer);
    return false;
  }
  fclose(output_file);
  return true;
}