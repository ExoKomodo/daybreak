#! /bin/bash

set -ex

bash ./compose_scripts/check_env.sh

# Bootstrap
bash ./compose_scripts/build.sh ./src/main.day -o ${DAYBREAK_BOOTSTRAP}

# Build with bootstrap
bash ./compose_scripts/build.sh ./src/main.day
# Test with bootstrap
bash ./compose_scripts/test.sh
# Memory check with bootstrap
bash ./compose_scripts/memory_check.sh
