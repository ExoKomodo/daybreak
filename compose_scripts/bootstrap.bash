#! /bin/bash

set -ex

TEMP=${CC_COMPILER}
# WASM does not support popen() currently, meaning daybreak is outside of the current WASM standard
if [ ${CC_COMPILER} = "zig-wasi" ]; then
	CC_COMPILER=zig
fi
if [ ${CC_COMPILER} = "clang-wasi" ]; then
	CC_COMPILER=clang
fi

bash ./compose_scripts/check_env.bash

${DAYBREAK_BOOTSTRAP} ./src/main.day -o ${DAYBREAK_BOOTSTRAP}

CC_COMPILER=${TEMP}
bash ./compose_scripts/check_env.bash
