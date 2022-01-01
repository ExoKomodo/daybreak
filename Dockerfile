FROM silkeh/clang:12

COPY . /app

WORKDIR /app

ENV JENKINS_USER=112
ENV JENKINS_GROUP=119

RUN bash admin_scripts/setup_jenkins_user.sh

RUN wget https://github.com/Kitware/CMake/releases/download/v3.22.1/cmake-3.22.1-linux-x86_64.sh -O /app/cmake.sh
