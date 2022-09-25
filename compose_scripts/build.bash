#! /bin/bash

set -ex

bash ./compose_scripts/check_env.bash
bash ./compose_scripts/bootstrap.bash

${DAYBREAK_BOOTSTRAP} $@
