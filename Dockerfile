FROM ubuntu:kinetic

ENV DEBIAN_FRONTEND=noninteractive

RUN apt-get update -y
RUN apt-get install -y curl

# Install gcc
RUN apt-get install -y gcc-12

# Install clang
RUN apt-get install -y clang-11

# Install zig
ENV ARCH=x86_64
ENV ZIG_VERSION=0.9.1
ENV ZIG_DIR=/zig-linux-${ARCH}-${ZIG_VERSION}
ENV ZIG_TARBALL=${ZIG_DIR}.tar.xz
RUN curl -O https://ziglang.org/download/${ZIG_VERSION}${ZIG_TARBALL}
RUN apt-get install -y xz-utils
RUN tar -xvf ${ZIG_TARBALL}
RUN rm ${ZIG_TARBALL}
RUN ln -s ${ZIG_DIR}/zig /usr/bin/zig
RUN which zig

# Install utilities
RUN apt-get install -y valgrind

COPY . /app
WORKDIR /app

RUN update-alternatives --install /usr/bin/gcc gcc $(which gcc-12) 1
RUN update-alternatives --install /usr/bin/clang clang $(which clang-11) 1
RUN update-alternatives --install /usr/bin/cc cc $(which gcc) 1
RUN update-alternatives --install /usr/bin/cc cc $(which clang) 2
RUN update-alternatives --install /usr/bin/cc cc $(which zig) 3
RUN ln -s /app/bootstrap/linux/daybreak /usr/bin/daybreak

ENV JENKINS_USER=112
ENV JENKINS_GROUP=119
ENV C_INCLUDE_PATH=/app/src/include:/app/tests/include

RUN bash admin_scripts/setup_jenkins_user.sh
