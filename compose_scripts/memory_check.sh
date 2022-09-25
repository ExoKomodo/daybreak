#! /bin/bash

set -ex

bash ./compose_scripts/check_env.sh

bash ./compose_scripts/test.sh valgrind --leak-check=full --error-exitcode=42
