FROM gcc:12

ENV DEBIAN_FRONTEND=noninteractive

RUN apt-get update -y
RUN apt-get install -y --no-install-recommends apt-utils
RUN apt-get install -y clang-11
RUN apt-get install -y valgrind

COPY . /app

WORKDIR /app

RUN update-alternatives --install /usr/bin/clang clang $(which clang-11) 1
RUN update-alternatives --install /usr/bin/cc cc $(which clang) 2
RUN ln -s /app/bootstrap/linux/daybreak /usr/local/bin/daybreak

ENV JENKINS_USER=112
ENV JENKINS_GROUP=119
ENV C_INCLUDE_PATH=/app/src/include:/app/tests/include

RUN bash admin_scripts/setup_jenkins_user.sh
