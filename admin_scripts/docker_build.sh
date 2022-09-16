#! /bin/bash

source ./admin_scripts/functions.sh

set -ex

TAGS=$(build_tags)

docker build ${TAGS} -f Dockerfiles/${NAME}/Dockerfile .
