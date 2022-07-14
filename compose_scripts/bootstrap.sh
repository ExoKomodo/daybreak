#! /bin/bash

set -ex

TEMP=${CC}
# WASM does not support popen() currently, meaning daybreak is outside of the current WASM standard
if [ ${CC} = "zig-wasi" ]; then
	CC=zig
fi

bash ./compose_scripts/check_env.sh

${DAYBREAK_BOOTSTRAP} ./src/main.day -o ${DAYBREAK_BOOTSTRAP}

CC=${TEMP}
bash ./compose_scripts/check_env.sh
