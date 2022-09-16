#! /bin/bash

function build_tag_values() {
	local REPO=exokomodo/daybreak
	local TAGS="${REPO}:${NAME}-${BUILD_ID}"

	if [[ ${BRANCH_NAME} = ${PROD_BRANCH} ]]; then
		TAGS="${TAGS} ${REPO}:${NAME}-latest"
	fi

	echo "${TAGS}"
}
