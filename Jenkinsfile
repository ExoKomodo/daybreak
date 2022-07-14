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
		stage('gcc') {
			environment {
				CC = "gcc"
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

		stage('clang') {
			environment {
				CC = "clang"
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

		stage('zig') {
			environment {
				CC = "zig"
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

                stage('zig-wasi') {
			environment {
				CC = "zig-wasi"
			}
			parallel {
				stage('[zig-wasi] Build Daybreak') {
					steps { 
						sh "docker-compose -p zig-wasi-build up ${COMPOSE_ARGS} build_daybreak"
					}
				}

				stage('[zig-wasi] Test') {
					steps {
						sh "docker-compose -p zig-wasi-test up ${COMPOSE_ARGS} test"
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
