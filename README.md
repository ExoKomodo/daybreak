# Daybreak
Programming language that compiles to C

## Important Links
- [Repository](https://github.com/ExoKomodo/Daybreak)
- [Jenkins](https://jenkins.exokomodo.com/job/Daybreak)
- [Language Cheat Sheet](https://docs.google.com/document/d/1VsP0L_J_NGatTqUZniUga4odmSZfCDRTvfQCVJQn9ac/edit?usp=sharing)

## Suggested VSCode Extensions
Reference [`devcontainer.json`](./.devcontainer/devcontainer.json)'s `extensions` array to see what VSCode extensions are recommended.

## CI/CD
[![Jenkins Build Status](http://jenkins.exokomodo.com/buildStatus/icon?job=Daybreak%2Fmain)](http://jenkins.exokomodo.com/job/Daybreak/job/main/)
![Bootstrap Workflow](https://github.com/ExoKomodo/Daybreak/actions/workflows/bootstrap.yml/badge.svg)

## Setup
Daybreak currently uses `cc` as the backing C compiler and will fail if this cannot be found.

### Environment
To develop the compiler, these env vars must be set (replacing `/path/to`):
- `C_INCLUDE_PATH=/path/to/daybreak/src/include:/path/to/daybreak/tests/include`

### Ubuntu

#### GCC (Ubuntu)
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

#### Clang (Ubuntu)
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

### Windows
Install [MSYS2](https://www.msys2.org/)

#### GCC (Windows)
Once installed, run the following commands to install all of the dependencies for GCC:
```bash
pacman -Syu
pacman -Su
pacman -S --needed base-devel mingw-w64-x86_64-toolchain # default=all is correct. ~1 gb of space needed.
```

Add `C:\msys64\mingw64\bin` to your `PATH` environment variable.

#### Clang (Windows)
```bash
echo "???"
```

### Mac
Give permissions to `/opt` 
```bash
sudo chmod -R 777 /opt
```
#### GCC (Mac)
```zsh
echo "unsupported"
```

#### Clang (Mac)
```zsh
echo "done"
```

## Build

### Ubuntu
```bash
./bootstrap/linux/daybreak ./src/main.day -o ./out/daybreak
```

### Windows
```powershell
.\bootstrap\windows\daybreak.exe .\src\main.day -o .\out\daybreak.exe
```

### Mac
```zsh
./bootstrap/osx/daybreak ./src/main.day -o ./out/daybreak
```

## Test

### Ubuntu
```bash
./bootstrap/linux/daybreak ./tests/test_main.day -o ./out/daybreak_test && ./out/daybreak_test
```

### Windows
```powershell
.\bootstrap\windows\daybreak.exe .\tests\test_main.day -o .\out\daybreak_test.exe && .\out\daybreak_test.exe
```

### Mac
```zsh
./bootstrap/osx/daybreak ./tests/test_main.day -o ./out/daybreak_test && ./out/daybreak_test
```
