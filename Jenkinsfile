def COMPOSE_ARGS = '--build --abort-on-container-exit'

pipeline {
	agent any

	options {
		disableConcurrentBuilds()
		ansiColor('xterm')
	}

	stages {
		stage('Build Daybreak') {
			steps {
				sh "docker-compose up ${COMPOSE_ARGS} build_daybreak"
			}
		}

		stage('Test') {
			steps {
				sh "docker-compose up ${COMPOSE_ARGS} test"
			}
		}

		stage('Memory Check') {
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
