#define DEBUG false

#include "test_foobar.h"
#include "test_hello_world.h"
#include "test_match.h"
#include "test_modules.h"
#include "test_pointers.h"
#include "test_types.h"
#include "test_variables.h"

#include <log/prelude.h>

int main() {
  bool is_success = true;
  is_success &= test_foobar();
  is_success &= test_hello_world();
  is_success &= test_match();
  is_success &= test_modules();
  is_success &= test_pointers();
  is_success &= test_types();
  is_success &= test_variables();

  assert(is_success);
  LOG_INFO("Successfully passed all tests!");
  return 0;
}
