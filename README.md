# Daybreak
Programming language that compiles to C

## Table of Contents
- [Important Links](#important-links)
- [Development](#development)
- [Daybreak Install](#daybreak-install)

## Important Links
- [Language Cheat Sheet](https://docs.google.com/document/d/1VsP0L_J_NGatTqUZniUga4odmSZfCDRTvfQCVJQn9ac/edit?usp=sharing)
- [Github Repository](https://github.com/ExoKomodo/Daybreak)
- [Jenkins](https://jenkins.exokomodo.com/job/Daybreak)
- [Jenkins - Base Image](https://jenkins.exokomodo.com/job/daybreak-base)
- [Jenkins - Devcontainer Image](https://jenkins.exokomodo.com/job/daybreak-devcontainer)
- [Docker Hub - Daybreak](https://hub.docker.com/repository/docker/exokomodo/daybreak)
- [Docker Hub - Development](https://hub.docker.com/repository/docker/exokomodo/development)

## Installation
To install daybreak locally, clone the Daybreak repo to your machine, and run `daybreak_install.bash`

### (Recommended) Git Clone via SSH:
Cloning via SSH will allow for you to contribute to Daybreak and push commits
```bash
# Clone repository locally
git clone git@github.com:ExoKomodo/Daybreak.git
# Temporarily move into Daybreak repo
cd ./Daybreak
# Follow the instructions of the install script
bash ./daybreak_install.bash
```

### (Not recommended) Git clone via HTTPS:
Cloning via HTTPS will only allow for you to clone the repo and install Daybreak. You will not be able to push commits to Github with an HTTPS-cloned repository.
```bash
# Clone repository locally
git clone https://github.com/ExoKomodo/Daybreak.git
# Temporarily move into Daybreak repo
cd ./Daybreak
# Follow the instructions of the install script
bash ./daybreak_install.bash
```

### Bootstrapping a new platform
To bootstrap a new compiler, a generated C source of Daybreak is needed to bootstrap the core Daybreak code into a binary. Clone the git repo either via HTTPS or SSH.
```bash
# Clone the repository locally
git clone git@github.com:ExoKomodo/Daybreak.git
# Temporarily move into Daybreak repo
cd ./Daybreak
# Set C_INCLUDE_PATH to use the includes of the cloned repo
export C_INCLUDE_PATH=./src/include:${C_INCLUDE_PATH}
```
Once the environment is setup, get the C source for the desired commit from the CI.
Sadly, Github's API is complex for this process and means that doing this without a web browser requires an API token.
The easiest method is to download the daybreak-linux.zip artifact from an action and work with that as so
```bash
unzip daybreak-linux.zip
cd daybreak-linux
cc main.day.c -o daybreak
```
Daybreak should now be fully bootstrapped and functioning on the new platform

## Suggested VSCode Extensions
Reference [`devcontainer.json`](./.devcontainer/devcontainer.json)'s `extensions` array to see what VSCode extensions are recommended.

## CI/CD
[![Jenkins Build Status](https://jenkins.exokomodo.com/buildStatus/icon?job=Daybreak/main)](http://jenkins.exokomodo.com/job/Daybreak/job/main/)
![Bootstrap Workflow](https://github.com/ExoKomodo/Daybreak/actions/workflows/bootstrap.yml/badge.svg)


## Development

### [Recommended] VSCode Dev Container
Using VSCode Dev Containers is the recommended way to develop Daybreak. To do so, either use [Github Codespaces](https://github.com/features/codespaces) or:
1. Install
[Remote - Containers](https://marketplace.visualstudio.com/items?itemName=ms-vscode-remote.remote-containers)
1. Follow the instructions [here](https://code.visualstudio.com/docs/remote/containers)
1. Follow the Ubuntu instructions below for running commands in the container

The Dev Container setup is finished and you can start developing on Daybreak right away using Docker Compose.

Use the following [Docker Compose](#docker-compose) instructions to develop Daybreak

### Docker Compose
Docker Compose provides a declarative way to define how docker containers should be run.

In Daybreak, this functionality is used to run different kinds of tasks within a container that is configured for Daybreak development.

The CI/CD pipeline for Daybreak simply calls compose services defined in [`docker-compose.yaml`](./docker-compose.yaml), so it is sufficient to use these same services for local development.
#### Environment
In the services, these environment variables are defined by default:
- `C_INCLUDE_PATH=/app/src/include:/app/tests/include` Defines the include paths for the underlying C compiler
- `CC_COMPILER=gcc` Defines which c compiler to use for compose services

These environment variables are defined by default for the VSCode Dev Container, but will need to be defined for local compose usage
- `DAYBREAK_BOOTSTRAP=/workspaces/Daybreak/bootstrap/linux/daybreak` Bootstrap executable location
- `OUT=/workspaces/Daybreak/out` Output directory for artifacts

#### Services
Services are defined in the [`docker-compose.yaml`](./docker-compose.yaml) file. For development purposes, here are the most important services and how to run them
- `build_daybreak`
  - builds the daybreak compiler using the existing bootstrap compiler
	- `docker-compose up build_daybreak`
- `test`
  - runs the daybreak compiler test suite on the current codebase, bootstrapping the compiler before running the test suite
	- `docker-compose up test`

### Native/Local Development
Daybreak currently uses `cc` as the backing C compiler and will fail if this cannot be found.

#### Environment
Skip if using VSCode Dev Containers, for development.

To develop the compiler locally, these env vars must be set (replacing `/path/to`):
- `C_INCLUDE_PATH=/path/to/daybreak/src/include:/path/to/daybreak/tests/include`  Defines the include paths for the underlying C compiler

#### Ubuntu

##### GCC (Ubuntu)
If `gcc` is not installed:
```bash
sudo apt update -y
sudo add-apt-repository -y ppa:ubuntu-toolchain-r/test
sudo apt install -y gcc-11
gcc-11 --version # Verifies installation
sudo update-alternatives --install /usr/bin/gcc gcc $(which gcc-11) 1 # Create /usr/bin/gcc binary if it does not exist, and links gcc-11 to gcc
sudo update-alternatives --install /usr/bin/cc cc $(which gcc) 1 # Create /usr/bin/cc binary if it does not exist, and links gcc to cc
# If cc already exists, this may fail and you will need to increment the number at the end of the command to lower the priority.
# cc should then be explicitly set to the compiler you want
CC_COMPILER=gcc
sudo update-alternatives --set cc $(which $CC_COMPILER)
```

##### Clang (Ubuntu)
If `clang` is not installed:
```bash
sudo apt update -y
sudo apt install -y clang-11
clang-11 --version # Verifies installation
sudo update-alternatives --install /usr/bin/clang clang $(which clang-11) 1 # Create /usr/bin/clang binary if it does not exist, and links clang-11 to clang
sudo update-alternatives --install /usr/bin/cc cc $(which clang) 1 # Create /usr/bin/cc binary if it does not exist, and links clang to cc
# If cc already exists, this may fail and you will need to increment the number at the end of the command to lower the priority.
# cc should then be explicitly set to the compiler you want
CC_COMPILER=clang
sudo update-alternatives --set cc $(which $CC_COMPILER)
```

##### Zig (Ubuntu)
If `zig` is not installed:
```bash
sudo apt update -y
sudo apt install -y curl

OS=linux
ARCH=x86_64
ZIG_VERSION=0.9.1 # Set version here
ZIG_DIR=zig-${OS}-${ARCH}-${ZIG_VERSION}
ZIG_TARBALL=${ZIG_DIR}.tar.xz
curl -O https://ziglang.org/download/${ZIG_VERSION}/${ZIG_TARBALL}
tar -xvf ${ZIG_TARBALL}
rm ${ZIG_TARBALL}
sudo echo "$(pwd)/${ZIG_DIR}/zig cc \$@" > /usr/bin/zig
sudo chmod +x /usr/bin/zig

sudo update-alternatives --install /usr/bin/cc cc $(which zig) 1 # Create /usr/bin/cc binary if it does not exist, and links zig to cc
# If cc already exists, this may fail and you will need to increment the number at the end of the command to lower the priority.
# cc should then be explicitly set to the compiler you want
CC_COMPILER=zig
sudo update-alternatives --set cc $(which $CC_COMPILER)
```

##### WASM (Ubuntu)
`zig` or `clang` can be used to compile WASM files as Daybreak backends with minimal configuration:
###### WASM via Zig
By modifying `/usr/bin/zig`, we can configure `zig` to compile WASM via wasi. Let's create an intercept compiler script called `zig-wasi`:
```bash
sudo echo "$(pwd)/${ZIG_DIR}/zig cc \$@" > /usr/bin/zig-wasi
sudo chmod +x /usr/bin/zig-wasi

sudo update-alternatives --install /usr/bin/cc cc $(which zig-wasi) 1 # Create /usr/bin/cc binary if it does not exist, and links zig-wasi to cc
# If cc already exists, this may fail and you will need to increment the number at the end of the command to lower the priority.
# cc should then be explicitly set to the compiler you want
CC_COMPILER=zig-wasi
sudo update-alternatives --set cc $(which $CC_COMPILER)
```

#### Windows
Install [MSYS2](https://www.msys2.org/)

##### GCC (Windows)
Once installed, run the following commands to install all of the dependencies for GCC:
```bash
pacman -Syu
pacman -Su
pacman -S --needed base-devel mingw-w64-x86_64-toolchain # default=all is correct. ~1 gb of space needed.
```

Add `C:\msys64\mingw64\bin` to your `PATH` environment variable.

##### Clang (Windows)
```bash
echo "???"
```

##### Zig (Windows)
```bash
echo "???"
```

#### Mac
##### GCC (Mac)
```zsh
echo "unsupported"
```

##### Clang (Mac)
```zsh
echo "done"
```
##### Zig (Mac)
If `zig` is not installed:
```bash
OS=macos
ARCH=x86_64 # aarch64 for Apple Silicon
ZIG_VERSION=0.9.1 # Set version here
ZIG_DIR=zig-${OS}-${ARCH}-${ZIG_VERSION}
ZIG_TARBALL=${ZIG_DIR}.tar.xz
curl -O https://ziglang.org/download/${ZIG_VERSION}/${ZIG_TARBALL}
tar -xvf ${ZIG_TARBALL}
rm ${ZIG_TARBALL}
sudo echo "$(pwd)/${ZIG_DIR}/zig cc \$@" > /usr/bin/zig
sudo chmod +x /usr/bin/zig

sudo update-alternatives --install /usr/bin/cc cc $(which zig) 1 # Create /usr/bin/cc binary if it does not exist, and links zig to cc
# If cc already exists, this may fail and you will need to increment the number at the end of the command to lower the priority.
# cc should then be explicitly set to the compiler you want
export CC_COMPILER=zig
```

### Build

#### Ubuntu
```bash
./bootstrap/linux/daybreak ./src/main.day -o ./out/daybreak
```

#### Windows
```powershell
.\bootstrap\windows\daybreak.exe .\src\main.day -o .\out\daybreak.exe
```

#### Mac
```zsh
./bootstrap/osx/daybreak ./src/main.day -o ./out/daybreak
```

#### Mac arm64 (e.g. M1, M2)
```zsh
./bootstrap/osx/daybreak_arm64 ./src/main.day -o ./out/daybreak_arm64
```

### Test

#### Ubuntu
```bash
./bootstrap/linux/daybreak ./tests/test_main.day -o ./out/daybreak_test && ./out/daybreak_test
```

#### Windows
```powershell
.\bootstrap\windows\daybreak.exe .\tests\test_main.day -o .\out\daybreak_test.exe && .\out\daybreak_test.exe
```

#### Mac
```zsh
./bootstrap/osx/daybreak ./tests/test_main.day -o ./out/daybreak_test && ./out/daybreak_test
```

#### Mac arm64
```zsh
./bootstrap/osx/daybreak_arm64 ./tests/test_main.day -o ./out/daybreak_test && ./out/daybreak_test
```
