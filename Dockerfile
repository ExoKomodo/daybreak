FROM gcc:11

RUN apt update -y
RUN apt install -y cmake valgrind

COPY . /app

WORKDIR /app

ENV JENKINS_USER=112
ENV JENKINS_GROUP=119


RUN bash admin_scripts/setup_jenkins_user.sh
