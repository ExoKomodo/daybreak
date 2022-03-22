#! /bin/bash

set -ex

WRAPPER=""

bash ./compose_scripts/check_env.sh
bash ./compose_scripts/bootstrap.sh

if [ $# -gt 0 ]; then
	WRAPPER="$@"
	echo "Wrapping test commands with: ${WRAPPER}"
fi

# Directly compile programs using the compiler executable
pushd ./examples
for example in *; do
	pushd ..
	${WRAPPER} ${DAYBREAK_BOOTSTRAP} ./examples/${example}/${example}.day
	popd
done
popd

bash ./compose_scripts/build.sh ./tests/test_main.day -o ${DAYBREAK_TEST}

# Run tests with the compiler's test executable
${WRAPPER} ${DAYBREAK_TEST}
