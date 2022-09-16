#! /bin/bash

function build_tags() {
	local TAGS="-t=${NAME}-${BUILD_ID}"

	if [[ ${BRANCH_NAME} = ${PROD_BRANCH} ]]; then
		TAGS="${TAGS} -t=${NAME}-latest"
	fi

	echo "${TAGS}"
}
