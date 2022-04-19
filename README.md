# Daybreak
Programming language that compiles to C

## Important Links
- [Repository](https://github.com/ExoKomodo/Daybreak)
- [Jenkins](https://jenkins.exokomodo.com/job/Daybreak)

## Suggested VSCode Extensions
Reference [`devcontainer.json`](./.devcontainer/devcontainer.json)'s `extensions` array to see what VSCode extensions are recommended.

## CI/CD
[![Jenkins Build Status](http://jenkins.exokomodo.com/buildStatus/icon?job=Daybreak%2Fmain)](http://jenkins.exokomodo.com/job/Daybreak/job/main/)

## Setup

### Setup on Windows
Install [MSYS2](https://www.msys2.org/)

Once installed, run the following commands to install all of the dependencies for GCC:
```bash
pacman -Syu
pacman -Su
pacman -S --needed base-devel mingw-w64-x86_64-toolchain # default=all is correct. ~1 gb of space needed.
```

Add `C:\msys64\mingw64\bin` to your `PATH` environment variable.

