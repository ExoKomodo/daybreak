# /bin/bash

set -ex

cd /app

bash ./compose_scripts/build.sh daybreak

VALGRIND_ARGS="-s --leak-check=full --show-leak-kinds=all --error-exitcode=42"

# Directly compile programs using the compiler executable
valgrind ${VALGRIND_ARGS} ./bin/daybreak ./examples/hello/hello.day

bash ./compose_scripts/build.sh daybreak_test

# Run tests with the compiler's test executable
valgrind ${VALGRIND_ARGS} ./bin/daybreak_test
