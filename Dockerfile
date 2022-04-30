FROM gcc:11

RUN apt update -y
RUN apt install clang-11 valgrind -y

COPY . /app

WORKDIR /app

RUN update-alternatives --install /usr/bin/cc cc $(which clang-11) 2

ENV JENKINS_USER=112
ENV JENKINS_GROUP=119
ENV C_INCLUDE_PATH=/app/src/include:/app/tests/include

RUN bash admin_scripts/setup_jenkins_user.sh