# Daybreak
Programming language that compiles to C

[![Jenkins Build Status](https://jenkins.exokomodo.com/job/Daybreak/job/main/badge/icon)](https://jenkins.exokomodo.com/job/Daybreak/job/main/)

## Important Links
- [Repository](https://github.com/ExoKomodo/Daybreak)
- [Jenkins](https://jenkins.exokomodo.com/job/Daybreak)

## Suggested VSCode Extensions
- [Better C++ Syntax](https://marketplace.visualstudio.com/items?itemName=jeff-hykin.better-cpp-syntax)
- [C/C++ Extension Pack](https://marketplace.visualstudio.com/items?itemName=ms-vscode.cpptools-extension-pack)
- [CMake](https://marketplace.visualstudio.com/items?itemName=twxs.cmake)
- [Daybreak Lang](https://marketplace.visualstudio.com/items?itemName=ExoKomodo.daybreak-lang)
- [Docker](https://marketplace.visualstudio.com/items?itemName=ms-azuretools.vscode-docker)
- [Jenkinsfile Support](https://marketplace.visualstudio.com/items?itemName=secanis.jenkinsfile-support)
- [Task Explorer](https://marketplace.visualstudio.com/items?itemName=spmeesseman.vscode-taskexplorer)
- [Trigger Task on Save](https://marketplace.visualstudio.com/items?itemName=Gruntfuggly.triggertaskonsave)
- [Visual Studio IntelliCode](https://marketplace.visualstudio.com/items?itemName=VisualStudioExptTeam.vscodeintellicode)

## Setup

### Setup on Windows
Install [MSYS2](https://www.msys2.org/)

Once installed, run the following commands to install all of the dependencies:
```bash
pacman -Syu
pacman -Su
pacman -S --needed base-devel mingw-w64-x86_64-toolchain # default=all is correct. ~1 gb of space needed.
```

Add `C:\msys64\mingw64\bin` to your `PATH` environment variable.

