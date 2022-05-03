def COMPOSE_ARGS = '--build --abort-on-container-exit'

pipeline {
	agent any

	options {
		disableConcurrentBuilds()
		ansiColor('xterm')
	}

	environment {
		DAYBREAK_BOOTSTRAP="./bootstrap/linux/daybreak"
		DAYBREAK_TEST="./out/daybreak_test"
	}

	stages {
		stage('[gcc] Build Daybreak') {
			environment {
				CC_COMPILER = "gcc"
			}

			steps {
				sh "docker-compose up ${COMPOSE_ARGS} build_daybreak"
			}
		}


		stage('[gcc] Test') {
			environment {
				CC_COMPILER = "gcc"
			}

			steps {
				sh "docker-compose up ${COMPOSE_ARGS} test"
			}
		}

		stage('[gcc] Memory Check') {
			environment {
				CC_COMPILER = "gcc"
			}

			steps {
				sh "docker-compose up ${COMPOSE_ARGS} memory_check"
			}
		}
		
		stage('[clang] Build Daybreak') {
			environment {
				CC_COMPILER = "clang"
			}

			steps {
				sh "docker-compose up ${COMPOSE_ARGS} build_daybreak"
			}
		}

		stage('[clang] Test') {
			environment {
				CC_COMPILER = "clang"
			}

			steps {
				sh "docker-compose up ${COMPOSE_ARGS} test"
			}
		}

		stage('[clang] Memory Check') {
			environment {
				CC_COMPILER = "clang"
			}

			steps {
				sh "docker-compose up ${COMPOSE_ARGS} memory_check"
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
