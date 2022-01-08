# /bin/bash

set -ex

cd /app

bash ./compose_scripts/configure.sh
cmake --build . --target $1 --
