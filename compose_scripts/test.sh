#! /bin/bash

set -ex

WRAPPER=""
if [[ ${CC_COMPILER} == *"wasi"* ]]; then
	WRAPPER=wasmtime
fi
DAYBREAK_TEST=${DAYBREAK_OUT}/daybreak_test
DAYBREAK_EULER=${DAYBREAK_OUT}/euler

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

# Directly compile Euler programs using the compiler executable
${WRAPPER} ${DAYBREAK_BOOTSTRAP} ./euler/euler.day
# Run build for actual run
bash ./compose_scripts/build.sh ./euler/euler.day -o ${DAYBREAK_EULER}
# Run euler problem solutions
${WRAPPER} ${DAYBREAK_EULER}

# Directly compile test programs using the compiler executable
${WRAPPER} ${DAYBREAK_BOOTSTRAP} ./tests/test_main.day
# Run build for actual run
bash ./compose_scripts/build.sh ./tests/test_main.day -o ${DAYBREAK_TEST}
# WASM does not support popen() currently, meaning daybreak is outside of the current WASM standard
if [ ${CC_COMPILER} != *"wasi"* ]; then
	# Run tests with the compiler's test executable
	${WRAPPER} ${DAYBREAK_TEST}
fi
