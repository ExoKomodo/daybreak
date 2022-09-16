#! /bin/bash

source ./admin_scripts/functions.sh

set -ex

TAGS=$(build_tags)

for tag in ${TAGS}; do
	docker push exokomodo/daybreak:${tag}
done
