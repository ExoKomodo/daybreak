#! /bin/bash

function build_tags() {
	NAME=$1
	shift

	local TAGS="-t ${NAME}-${BUILD_NUMBER} -t"

	if [[ ${BRANCH_NAME} = ${PROD_BRANCH} ]]; then
		TAGS="${TAGS} -t ${NAME}-latest"
	fi

	echo "${TAGS}"
}
