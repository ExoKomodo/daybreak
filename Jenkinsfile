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
		stage('Build all') {
			parallel {
				stage ("[gcc] Build Daybreak") {
					environment {
						CC_COMPILER = "gcc"
					}
					steps {
						sh "docker-compose up ${COMPOSE_ARGS} -p gcc-build build_daybreak"
					}
				}

				stage('[clang] Build Daybreak') {
					environment {
						CC_COMPILER = "clang"
					}
					steps { 
						sh "docker-compose up ${COMPOSE_ARGS} -p clang-build build_daybreak"
					}
				}
			}
		}

		stage('Test all') {
			parallel {
				stage('[gcc] Test') {
					environment {
						CC_COMPILER = "gcc"
					}
					steps {
						sh "docker-compose up ${COMPOSE_ARGS} -p gcc-test test"
					}
				}

				stage('[clang] Test') {
					environment {
						CC_COMPILER = "clang"
					}
					steps {
						sh "docker-compose up ${COMPOSE_ARGS} -p clang-test test"
					}
				}
			}
		}

		stage('Memory Check all') {
			parallel {
				stage('[gcc] Memory Check') {
					environment {
						CC_COMPILER = "gcc"
					}
					steps {
						sh "docker-compose up ${COMPOSE_ARGS} -p gcc-memcheck memory_check"
					}
				}

				stage('[clang] Memory Check') {
					environment {
						CC_COMPILER = "clang"
					}
					steps {
						sh "docker-compose up ${COMPOSE_ARGS} -p clang-memcheck memory_check"
					}
				}
			}
		}
	}

	post {
		always {
			sh "docker-compose up ${COMPOSE_ARGS} -p fix_ownership"
		}
		cleanup {
			sh "bash ./admin_scripts/cleanup.sh"
		}
	}
}
