#! /bin/bash

groupadd -r -f -g ${JENKINS_GROUP} jenkins
useradd -r -u ${JENKINS_USER} -g ${JENKINS_GROUP} jenkins