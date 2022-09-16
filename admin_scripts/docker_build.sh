#! /bin/bash

source ./admin_scripts/functions.sh

set -ex

NAME=$1
shift

TAGS=$(build_tags $NAME)

docker build ${TAGS} -f Dockerfiles/${NAME}/Dockerfile .
