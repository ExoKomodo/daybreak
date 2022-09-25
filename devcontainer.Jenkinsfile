def COMPOSE_ARGS = '--build --abort-on-container-exit'

pipeline {
	agent any

	options {
		disableConcurrentBuilds()
		ansiColor('xterm')
	}

	environment {
		PROD_BRANCH="main"
		DAYBREAK_BOOTSTRAP="./bootstrap/linux/daybreak"
		DAYBREAK_OUT="./out"
		REGISTRY_PASSWORD=credentials("docker-password")
		REGISTRY_USERNAME=credentials("docker-username")
		NAME="devcontainer"
	}

	stages {
		stage ("Docker Login") {
			steps {
				sh "bash ./cicada/ci/container_login.bash"
			}
		}

		stage ("Build") {
			environment {
				CC_COMPILER = "gcc"
			}
			steps {
				sh "bash ./cicada/ci/container_build.bash"
			}
		}

		stage ("Push") {
			steps {
				sh "bash ./cicada/ci/container_push.bash"
			}
		}
	}

	post {
		always {
			sh "docker-compose up ${COMPOSE_ARGS} fix_ownership"
		}

		cleanup {
			sh "bash ./cicada/ci/cleanup.bash"
		}
	}
}
