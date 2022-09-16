#! /bin/bash

source ./admin_scripts/functions.sh

set -ex

TAGS=$(build_tags $1)

docker push exokomodo/daybreak:${}
