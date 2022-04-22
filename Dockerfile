FROM gcc:11

RUN apt update -y
RUN apt install valgrind -y

ENV C_INCLUDE_PATH=/app/src/include:/app/tests/include

COPY . /app

WORKDIR /app

ENV JENKINS_USER=112
ENV JENKINS_GROUP=119

RUN bash admin_scripts/setup_jenkins_user.sh
