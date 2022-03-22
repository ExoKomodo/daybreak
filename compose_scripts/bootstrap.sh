#! /bin/bash

set -ex

bash ./compose_scripts/check_env.sh

${DAYBREAK_BOOTSTRAP} ./src/main.day -o ${DAYBREAK_BOOTSTRAP}