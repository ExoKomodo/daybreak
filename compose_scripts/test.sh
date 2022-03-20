#! /bin/bash

set -ex

WRAPPER=""

bash ./compose_scripts/check_env.sh

if [ $# -gt 0 ]; then
	WRAPPER="$@"
	echo "Wrapping test commands with: ${WRAPPER}"
fi

# Directly compile programs using the compiler executable
${WRAPPER} ${DAYBREAK_BOOTSTRAP} ./examples/foobar/foobar.day
${WRAPPER} ${DAYBREAK_BOOTSTRAP} ./examples/hello/hello.day
${WRAPPER} ${DAYBREAK_BOOTSTRAP} ./examples/match/match.day
${WRAPPER} ${DAYBREAK_BOOTSTRAP} ./examples/modules/modules.day
${WRAPPER} ${DAYBREAK_BOOTSTRAP} ./examples/pointers/pointers.day
${WRAPPER} ${DAYBREAK_BOOTSTRAP} ./examples/types/types.day
${WRAPPER} ${DAYBREAK_BOOTSTRAP} ./examples/variables/variables.day

bash ./compose_scripts/build.sh ./tests/test_main.day -o ${DAYBREAK_TEST_BOOTSTRAP}

# Run tests with the compiler's test executable
${WRAPPER} ${DAYBREAK_TEST_BOOTSTRAP}
