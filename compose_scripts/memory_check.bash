#! /bin/bash

set -ex

bash ./compose_scripts/check_env.bash

bash ./compose_scripts/test.bash valgrind --leak-check=full --error-exitcode=42
