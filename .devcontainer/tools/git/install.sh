#! /bin/bash

set -ex

apt-get install -y git
cp ./.devcontainer/tools/git/gitconfig ~/.gitconfig
