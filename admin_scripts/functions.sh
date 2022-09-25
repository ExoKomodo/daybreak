#! /bin/bash

function build_tag_values() {
	if [[ ${BRANCH_NAME} = ${PROD_BRANCH} ]]; then
		local REPO=exokomodo/daybreak

		local TAGS="${REPO}:${NAME}-${BUILD_ID} ${REPO}:${NAME}-latest"
	else
		local REPO=exokomodo/development

		local TAGS="${REPO}:${BRANCH_NAME}-${NAME}-${BUILD_ID} ${REPO}:${BRANCH_NAME}-${NAME}-latest"
	fi

	echo "${TAGS}"
}
