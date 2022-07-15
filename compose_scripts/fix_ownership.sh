#! /bin/bash

set -ex

if [ -z ${JENKINS_USER} ];
then
	echo "Must define env var: JENKINS_USER"
	exit 1
fi

if [ -z ${JENKINS_GROUP} ];
then
	echo "Must define env var: JENKINS_GROUP"
	exit 1
fi

chown -R ${JENKINS_USER}:${JENKINS_GROUP} .
