def COMPOSE_ARGS = '--build --abort-on-container-exit'

pipeline {
	agent any

	options {
		disableConcurrentBuilds()
		ansiColor('xterm')
	}

	environment {
		DAYBREAK_BOOTSTRAP="./bootstrap/linux/daybreak"
		DAYBREAK_OUT="./out"
		REGISTRY_PASSWORD=credentials("docker-password")
		REGISTRY_USERNAME=credentials("docker-username")
	}

	stages {
		stage ("Docker Login") {
			steps {
				sh "bash ./admin_scripts/docker_login.sh"
			}
		}

		stage ("Build") {
			environment {
				CC_COMPILER = "gcc"
			}
			steps {
				sh "bash ./admin_scripts/docker_build.sh"
			}
		}

		stage ("Push") {
			steps {
				sh "bash ./admin_scripts/docker_push.sh"
			}
		}
	}

	post {
		always {
			sh "docker-compose up ${COMPOSE_ARGS} fix_ownership"
		}

		cleanup {
			sh "bash ./admin_scripts/cleanup.sh"
		}
	}
}
