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
	}

	stages {
		stage('GCC') {
			environment {
				CC_COMPILER = "gcc"
			}

			parallel {
				stage ("[gcc] Build Daybreak") {
					steps {
						sh "docker-compose up ${COMPOSE_ARGS} build_daybreak"
					}
				}

				stage('[gcc] Test') {
					steps {
						sh "docker-compose up ${COMPOSE_ARGS} test"
					}
				}

				stage('[gcc] Memory Check') {
					steps {
						sh "docker-compose up ${COMPOSE_ARGS} memory_check"
					}
				}
			}
		}

		stage('Clang') {
			environment {
				CC_COMPILER = "clang"
			}

			parallel {
				stage('[clang] Build Daybreak') {
					steps {
						sh "docker-compose up ${COMPOSE_ARGS} build_daybreak"
					}
				}

				stage('[clang] Test') {
					steps {
						sh "docker-compose up ${COMPOSE_ARGS} test"
					}
				}

				stage('[clang] Memory Check') {
					steps {
						sh "docker-compose up ${COMPOSE_ARGS} memory_check"
					}
				}
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
