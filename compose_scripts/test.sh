# /bin/bash

set -ex

# Directly compile programs using the compiler executable
./build/bin/daybreak ./examples/hello.day

# Run tests with the compiler's test executable
./build/bin/daybreak_test .