#! /bin/bash

set -ex

bash ./compose_scripts/check_env.sh

${DAYBREAK_BOOTSTRAP} $@
