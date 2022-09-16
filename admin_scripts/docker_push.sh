#! /bin/bash

source ./admin_scripts/functions.sh

set -ex

TAG_VALUES=$(build_tags)

for tag in ${TAG_VALUES}; do
	docker push exokomodo/daybreak:${tag}
done
