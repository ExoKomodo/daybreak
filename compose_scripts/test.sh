# /bin/bash

set -ex

WRAPPER=""

if [ $# -gt 0 ]; then
	WRAPPER="$1"
	echo "Wrapping test commands with: ${WRAPPER}"
fi

cd /app

bash ./compose_scripts/build.sh daybreak

# Directly compile programs using the compiler executable
${WRAPPER} ./bin/daybreak ./examples/hello/hello.day
${WRAPPER} ./bin/daybreak ./examples/foobar/foobar.day

bash ./compose_scripts/build.sh daybreak_test

# Run tests with the compiler's test executable
${WRAPPER} ./bin/daybreak_test
