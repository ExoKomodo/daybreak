#! /bin/bash

set -e

COMPILER_BACKENDS="gcc clang zig"

function _choose_compiler_backend() {
	if [ $# -eq 0 ]; then
		echo "Could not find a supported compiler backend!"
		echo "Please install and make available on PATH one of the following:"
		echo ${COMPILER_BACKENDS}
		exit 1
	fi

	CC_COMPILER=$1
	shift
	echo "Checking for compiler backend ${CC_COMPILER}"
	if ! command -v ${CC_COMPILER} &> /dev/null; then
		echo "Missing compiler backend ${CC_COMPILER}"
		set_compiler $@
	fi
}

function bootstrap_install() {
	echo "Bootstrapping Daybreak for the local installation..."
	DAYBREAK_BOOTSTRAP=${DAYBREAK_REPO_FOLDER}/bootstrap/${OS}/daybreak
	DAYBREAK_OUTPUT=${DAYBREAK_HOME}/bin/daybreak
	if [[ ${OS} = "windows" ]]; then
		DAYBREAK_BOOTSTRAP=${DAYBREAK_BOOTSTRAP}.exe
		DAYBREAK_OUTPUT=${DAYBREAK_OUTPUT}.exe
	fi
	export C_INCLUDE_PATH=${DAYBREAK_SOURCE_FOLDER}/include
	${DAYBREAK_BOOTSTRAP} ${DAYBREAK_SOURCE_FOLDER}/main.day -o ${DAYBREAK_OUTPUT} >> /dev/null
	echo "Successfully bootstrapped Daybreak!"
}

function print_export_env() {
	echo ""
	echo "Identifying default shell and the associated rcfile..."
	RC_FILE=${HOME}/.$(basename $(echo ${SHELL}))rc
	echo "Identified:"
	echo "  shell  -> ${SHELL}"
	echo "  rcfile -> ${RC_FILE}"

	echo ""
	echo "##############"
	echo "# Next Steps #"
	echo "##############"
	echo "Run all of the following commands in your terminal to finish the Daybreak installation"
	echo "The first two commands persist the configuration chosen by this install script"
	echo "The third command adds daybreak tools to your PATH for every login session and not just the current login session"
	echo ""
	echo "echo 'export CC_COMPILER=${CC_COMPILER}' >> ${RC_FILE}"
	echo "echo 'export DAYBREAK_HOME=${DAYBREAK_HOME}' >> ${RC_FILE}"
	echo 'echo '"'"'export PATH=${DAYBREAK_HOME}/bin:${PATH}'"'"''" >> ${RC_FILE}"
	echo ""
	echo "Daybreak should now be fully configured and available!"
}

function set_default_env() {
	echo "Checking environment variables and temporarily setting default values for unset env vars"
	echo ""
	echo "Identifying OS..."
	case "$(uname -s)" in
		Linux*)     OS=linux;;
		Darwin*)    OS=osx;;
		CYGWIN*)    OS=windows;;
		MINGW*)     OS=windows;;
		*)          echo "Failed to identify OS"; exit 1;;
	esac
	echo "Identified OS as ${OS}"
	echo ""

	if [ -z ${CC_COMPILER} ]; then
		_choose_compiler_backend ${COMPILER_BACKENDS}
		echo "CC_COMPILER set to default: ${CC_COMPILER} -> $(which ${CC_COMPILER})"
	else
		echo "CC_COMPILER already set to: ${CC_COMPILER} -> $(which ${CC_COMPILER})"
	fi

	if [ -z ${DAYBREAK_HOME} ]; then
		DAYBREAK_HOME=${HOME}/.daybreak
		echo "DAYBREAK_HOME set to default: ${DAYBREAK_HOME}"
	else
		echo "DAYBREAK_HOME already set to: ${DAYBREAK_HOME}"
	fi

        if [[ ${OS} = "linux" ]]; then
		update-alternatives --set cc $(which ${CC_COMPILER})
	fi
	echo ""
}

if [ $# -eq 0 ]; then
	DAYBREAK_REPO_FOLDER=$(cd $(dirname ${BASH_SOURCE[0]}) && pwd)
	DAYBREAK_SOURCE_FOLDER=${DAYBREAK_REPO_FOLDER}/src
	echo ${DAYBREAK_SOURCE_FOLDER}
else
	DAYBREAK_REPO_FOLDER=$1
	shift
	DAYBREAK_SOURCE_FOLDER=${DAYBREAK_REPO_FOLDER}/src
fi

set_default_env

bootstrap_install

print_export_env
