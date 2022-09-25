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
ENV WASI_SYSROOT=wasi-sysroot-16.0
ENV WASI_SYSROOT_PATH=/wasi/${WASI_SYSROOT}
RUN curl -o ${WASI_SYSROOT}.tar.gz https://objects.githubusercontent.com/github-production-release-asset-2e65be/174204333/44f44441-cc60-43f2-a518-7e4cb42297b5?X-Amz-Algorithm=AWS4-HMAC-SHA256&X-Amz-Credential=AKIAIWNJYAX4CSVEH53A%2F20220925%2Fus-east-1%2Fs3%2Faws4_request&X-Amz-Date=20220925T054911Z&X-Amz-Expires=300&X-Amz-Signature=fdce4eead282ddc4f9f3fe45f05d4f7598e6f6add057d4193b8de08d2e4ed5b7&X-Amz-SignedHeaders=host&actor_id=17893076&key_id=0&repo_id=174204333&response-content-disposition=attachment%3B%20filename%3Dwasi-sysroot-16.0.tar.gz&response-content-type=application%2Foctet-stream
RUN tar -xf ${WASI_SYSROOT}.tar.gz

# Install zig backend
ENV ARCH=x86_64
ENV ZIG_VERSION=0.9.1
ENV ZIG_DIR=/zig-linux-${ARCH}-${ZIG_VERSION}
ENV ZIG_TARBALL=${ZIG_DIR}.tar.xz
RUN curl -O https://ziglang.org/download/${ZIG_VERSION}${ZIG_TARBALL}
RUN tar -xvf ${ZIG_TARBALL}
RUN rm ${ZIG_TARBALL}
RUN echo '${ZIG_DIR}/zig cc $@' > /usr/bin/zig
RUN chmod +x /usr/bin/zig

# Create zig-wasi backend
RUN echo '${ZIG_DIR}/zig cc --target=wasm32-wasi --sysroot ${WASI_SYSROOT_PATH} $@' > /usr/bin/zig-wasi
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
