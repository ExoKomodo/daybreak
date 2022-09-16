#! /bin/bash

source ./admin_scripts/functions.sh

set -ex

TAG_VALUES=$(build_tags)

TAGS=""
for tag in ${TAG_VALUES}; do
	TAGS="${TAGS} -t ${tag}"
done

docker build ${TAGS} -f Dockerfiles/${NAME}/Dockerfile .
