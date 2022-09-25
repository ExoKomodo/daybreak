FROM ubuntu:kinetic

ENV DEBIAN_FRONTEND=noninteractive

RUN apt-get update -y
RUN apt-get install -y curl
RUN apt-get install -y xz-utils

# Install gcc backend
RUN apt-get install -y gcc-12

# Install clang backend
RUN apt-get install -y clang-11

# Install WASI
WORKDIR /wasi
ARG WASI_SYSROOT=wasi-sysroot-16.0
ARG WASI_SYSROOT_TARBALL=${WASI_SYSROOT}.tar.gz
ARG WASI_SYSROOT_PATH=/wasi/${WASI_SYSROOT}
RUN curl -O "https://github.com/ExoKomodo/Daybreak/raw/main/deps/${WASI_SYSROOT_TARBALL}"
RUN tar -xf ${WASI_SYSROOT_TARBALL}

# Install zig backend
ARG ARCH=x86_64
ARG ZIG_VERSION=0.9.1
ARG ZIG_DIR=/zig-linux-${ARCH}-${ZIG_VERSION}
ARG ZIG_TARBALL=${ZIG_DIR}.tar.xz
RUN curl -O https://ziglang.org/download/${ZIG_VERSION}${ZIG_TARBALL}
RUN tar -xvf ${ZIG_TARBALL}
RUN rm ${ZIG_TARBALL}
RUN echo '${ZIG_DIR}/zig cc $@' > /usr/bin/zig
RUN chmod +x /usr/bin/zig

# Create zig-wasi backend
RUN echo "${ZIG_DIR}/zig cc --target=wasm32-wasi --sysroot ${WASI_SYSROOT_PATH} \$@" > /usr/bin/zig-wasi
RUN chmod +x /usr/bin/zig-wasi

# Install utilities
RUN apt-get install -y valgrind
RUN curl https://wasmtime.dev/install.sh -sSf | bash
ENV PATH="${HOME}/.wasmtime/bin:${PATH}"

# Register backends
RUN update-alternatives --install /usr/bin/gcc gcc $(which gcc-12) 5
RUN update-alternatives --install /usr/bin/cc cc $(which gcc) 4
RUN update-alternatives --install /usr/bin/clang clang $(which clang-11) 3
RUN update-alternatives --install /usr/bin/cc cc $(which clang) 2
RUN update-alternatives --install /usr/bin/cc cc $(which zig) 1
RUN update-alternatives --install /usr/bin/cc cc $(which zig-wasi) 0
RUN ln -s /app/bootstrap/linux/daybreak /usr/bin/daybreak

ENV JENKINS_USER=112
ENV JENKINS_GROUP=119

RUN groupadd -r -f -g ${JENKINS_GROUP} jenkins
RUN useradd -r -u ${JENKINS_USER} -g ${JENKINS_GROUP} jenkins

# Assumes the git repo will be mounted at /app
ENV C_INCLUDE_PATH=/app/src/include:/app/tests/include
