FROM ubuntu:kinetic

ARG MOUNT_DIRECTORY=/app

ENV DEBIAN_FRONTEND=noninteractive

RUN apt-get update -y --fix-missing
RUN apt-get install -qy apt-utils
RUN apt-get install -qy curl
RUN apt-get install -qy valgrind
RUN apt-get install -qy xz-utils

# Install gcc backend
RUN apt-get install -qy gcc-12

# Install clang backend
RUN apt-get install -qy clang-11

# Install WASI
WORKDIR /wasi
RUN curl -O https://raw.githubusercontent.com/ExoKomodo/Daybreak/main/deps/wasi-sysroot-16.0.tar.gz
RUN tar -xf wasi-sysroot-16.0.tar.gz
RUN rm wasi-sysroot-16.0.tar.gz
WORKDIR /

# Install wasmtime
RUN curl https://wasmtime.dev/install.sh -sSf | bash
ENV PATH="${HOME}/.wasmtime/bin:${PATH}"

# Install zig backend
ARG ARCH=x86_64
ARG ZIG_VERSION=0.9.1
ARG ZIG_DIR=/zig-linux-${ARCH}-${ZIG_VERSION}
ARG ZIG_TARBALL=${ZIG_DIR}.tar.xz

RUN curl -O https://ziglang.org/download/${ZIG_VERSION}${ZIG_TARBALL}
RUN tar -xf ${ZIG_TARBALL}
RUN rm ${ZIG_TARBALL}
RUN echo "${ZIG_DIR}/zig cc \$@" > /usr/bin/zig
RUN chmod +x /usr/bin/zig

# Create zig-wasi backend
RUN echo "${ZIG_DIR}/zig cc --target=wasm32-wasi --sysroot /wasi/wasi-sysroot-16.0 \$@" > /usr/bin/zig-wasi
RUN chmod +x /usr/bin/zig-wasi

# Register backends
RUN update-alternatives --install /usr/bin/gcc gcc $(which gcc-12) 5
RUN update-alternatives --install /usr/bin/cc cc $(which gcc) 4
RUN update-alternatives --install /usr/bin/clang clang $(which clang-11) 3
RUN update-alternatives --install /usr/bin/cc cc $(which clang) 2
RUN update-alternatives --install /usr/bin/cc cc $(which zig) 1
RUN update-alternatives --install /usr/bin/cc cc $(which zig-wasi) 0

# Add jenkins user and group
ENV CICADA_JENKINS_USER=112
ENV CICADA_JENKINS_GROUP=119

RUN groupadd -r -f -g ${CICADA_JENKINS_GROUP} jenkins
RUN useradd -r -u ${CICADA_JENKINS_USER} -g ${CICADA_JENKINS_GROUP} jenkins

# Set env vars that have no dependent commands
ENV C_INCLUDE_PATH=${MOUNT_DIRECTORY}/src/include:${MOUNT_DIRECTORY}/tests/include

WORKDIR ${MOUNT_DIRECTORY}
