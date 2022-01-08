#define DEBUG true

#include "test_hello_world.h"

#include <log/prelude.h>

int main() {
  bool is_success = true;
  is_success &= test_hello_world();

  assert(is_success);
  LOG_INFO("Successfully passed all tests!");
  return 0;
}
