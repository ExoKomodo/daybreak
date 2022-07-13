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
						sh "docker-compose -p gcc-build up ${COMPOSE_ARGS} build_daybreak"
					}
				}
				
				stage('[gcc] Test') {
					steps {
						sh "docker-compose -p gcc-test up ${COMPOSE_ARGS} test"
					}
				}

				stage('[gcc] Memory Check') {
					steps {
						sh "docker-compose -p gcc-memcheck up ${COMPOSE_ARGS} memory_check"
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
						sh "docker-compose -p clang-build up ${COMPOSE_ARGS} build_daybreak"
					}
				}

				stage('[clang] Test') {
					steps {
						sh "docker-compose -p clang-test up ${COMPOSE_ARGS} test"
					}
				}
				
				stage('[clang] Memory Check') {
					steps {
						sh "docker-compose -p clang-memcheck up ${COMPOSE_ARGS} memory_check"
					}
				}
			}
		}

		stage('Zig') {
			environment {
				CC_COMPILER = "zig"
			}
			parallel {
				stage('[zig] Build Daybreak') {
					steps { 
						sh "docker-compose -p zig-build up ${COMPOSE_ARGS} build_daybreak"
					}
				}

				stage('[zig] Test') {
					steps {
						sh "docker-compose -p zig-test up ${COMPOSE_ARGS} test"
					}
				}
				
				stage('[zig] Memory Check') {
					steps {
						sh "docker-compose -p zig-memcheck up ${COMPOSE_ARGS} memory_check"
					}
				}
			}
		}
	}

	post {
		always {
			sh "docker-compose -p fix_ownership up ${COMPOSE_ARGS}"
		}
		cleanup {
			sh "bash ./admin_scripts/cleanup.sh"
		}
	}
}
