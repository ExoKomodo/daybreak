FROM debian:11-slim

RUN apt update -y
RUN apt install -y --no-install-recommends apt-utils
RUN apt install -y build-essential
RUN apt install -y clang-11
RUN apt install -y valgrind

COPY . /app

WORKDIR /app

RUN update-alternatives --install /usr/bin/clang clang $(which clang-11) 1
RUN update-alternatives --install /usr/bin/cc cc $(which clang) 2

ENV JENKINS_USER=112
ENV JENKINS_GROUP=119
ENV C_INCLUDE_PATH=/app/src/include:/app/tests/include

RUN bash admin_scripts/setup_jenkins_user.sh
