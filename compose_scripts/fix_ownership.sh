#! /bin/bash

set -ex

bash ./compose_scripts/check_env.sh

chown -R ${JENKINS_USER}:${JENKINS_GROUP} .
