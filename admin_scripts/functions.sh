#! /bin/bash

function build_tags() {
	local TAGS="${NAME}-${BUILD_ID}"

	if [[ ${BRANCH_NAME} = ${PROD_BRANCH} ]]; then
		TAGS="${TAGS} ${NAME}-latest"
	fi

	echo "${TAGS}"
}
