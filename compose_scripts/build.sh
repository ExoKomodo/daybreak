#! /bin/bash

set -ex

bash ./compose_scripts/check_env.sh
bash ./compose_scripts/bootstrap.sh

${DAYBREAK_BOOTSTRAP} $@
