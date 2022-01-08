# /bin/bash

set -ex

cd /app

bash ./compose_scripts/build.sh daybreak

# Directly compile programs using the compiler executable
./bin/daybreak ./examples/hello/hello.day

bash ./compose_scripts/build.sh daybreak_test

# Run tests with the compiler's test executable
./bin/daybreak_test
