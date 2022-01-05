#include "test_hello_world.h"

int main(int argc, const char** argv) {
  if (argc < 2) {
    puts("Usage: daybreak_test <test_file_root_path>");
    return 1;
  }
  const char* test_file_root_path = argv[1];
  test_hello_world(test_file_root_path);
  return 0;
}
