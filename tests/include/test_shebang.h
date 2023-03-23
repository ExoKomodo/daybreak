#include <assert.h>
#include <stdbool.h>
#include <stdio.h>

#include <helpers/system.h>
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
  const int error = daybreak_compile(
    (DaybreakArgs) {
      .source_file_path = SHEBANG,
      .output_file_path = SHEBANG_EXECUTABLE,
    }
  );
  if (error != 0) {
    LOG_ERROR("Failed compiling shebang program via compiler API");
    return false;
  }

  return true;
}