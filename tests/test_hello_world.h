#include <assert.h>
#include <stdbool.h>
#include <stdbool.h>

#include <api/prelude.h>

#if defined(_WIN32) || defined(_WIN64)
  #define HELLO_WORLD "\\examples\\hello.day"
#else
  #define HELLO_WORLD "/examples/hello.day"
#endif

bool test_hello_world(const char* test_file_root_path) {
  const size_t test_file_path_length = strlen(test_file_root_path) + strlen(HELLO_WORLD) + 1;
  char* test_file_path = malloc(test_file_path_length);
  memset(test_file_path, 0, test_file_path_length);
  strcat(test_file_path, test_file_root_path);
  strcat(test_file_path, HELLO_WORLD);
  return compile(test_file_path);
}
