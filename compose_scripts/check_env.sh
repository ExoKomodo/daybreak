#! /bin/bash

set -ex

if [ -z ${DAYBREAK_BOOTSTRAP} ];
then
	echo "Must define env var: DAYBREAK_BOOTSTRAP"
	exit 1
fi

if [ -z ${DAYBREAK_OUT} ];
then
	echo "Must define env var: DAYBREAK_OUT"
	exit 1
fi

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

if [ -n ${CC_COMPILER} ];
then
	update-alternatives --set cc $(which $CC_COMPILER)
fi
