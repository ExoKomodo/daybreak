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

	CC=$1
	shift
	echo "Checking for compiler backend ${CC}"
	if ! command -v ${CC} &> /dev/null; then
		echo "Missing compiler backend ${CC}"
		set_compiler $@
	fi
}

function bootstrap_install() {
	DAYBREAK_BOOTSTRAP=${DAYBREAK_SOURCE_FOLDER}/bootstrap/${OS}/daybreak
	DAYBREAK_OUTPUT=${DAYBREAK_HOME}/bin/daybreak
	if [[ ${OS} = "windows" ]]; then
		DAYBREAK_BOOTSTRAP=${DAYBREAK_BOOTSTRAP}.exe
		DAYBREAK_OUTPUT=${DAYBREAK_OUTPUT}.exe
	fi
	C_INCLUDE_PATH=${DAYBREAK_SOURCE_FOLDER}/src/include
	${DAYBREAK_BOOTSTRAP} ${DAYBREAK_SOURCE_FOLDER}/src/main.day -o ${DAYBREAK_OUTPUT}
}

function print_export_env() {
	echo "Add the following to your rcfile of choice to preserve the installed configuration:"
	echo "  export CC=${CC}"
	echo "  export DAYBREAK_HOME=${DAYBREAK_HOME}"
	echo ""
	echo "Add the following to your rcfile of choice to make daybreak tools available:"
	echo "  export PATH=${DAYBREAK_HOME}/bin:\${PATH}"
}

function set_default_env() {
	echo "Checking environment variables and temporarily setting default values for unset env vars"

	echo "Identifying OS"
	case "$(uname -s)" in
			Linux*)     OS=linux;;
			Darwin*)    OS=osx;;
			CYGWIN*)    OS=windows;;
			MINGW*)     OS=windows;;
			*)          echo "Failed to identify OS"; exit 1;;
	esac

	if [ -z ${CC} ]; then
		_choose_compiler_backend ${COMPILER_BACKENDS}
		echo "CC set to default: ${CC} -> $(which ${CC})"
	else
		echo "CC already set to: ${CC} -> $(which ${CC})"
	fi
	
	if [ -z ${DAYBREAK_HOME} ]; then
		DAYBREAK_HOME=${HOME}/.daybreak
		echo "DAYBREAK_HOME set to default: ${DAYBREAK_HOME}"
	else
		echo "DAYBREAK_HOME already set to: ${DAYBREAK_HOME}"
	fi

	update-alternatives --set cc $(which ${CC})

	# TODO: Check if any env vars are yet to be defined and given appropriate defaults
}

if [ $# -eq 0 ]; then
	DAYBREAK_SOURCE_FOLDER=.
else
	DAYBREAK_SOURCE_FOLDER=$1
	shift
fi

set_default_env

bootstrap_install

print_export_env
