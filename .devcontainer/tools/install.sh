#! /bin/bash

set -ex

apt-get update -y

apt-get install -y less locales neofetch
locale-gen en_US.UTF-8

bash ./.devcontainer/tools/docker/install.sh
bash ./.devcontainer/tools/git/install.sh
bash ./.devcontainer/tools/vim/install.sh
bash ./.devcontainer/tools/zsh/install.sh

ln -s -f /workspaces/Daybreak/bootstrap/linux/daybreak /usr/local/bin/daybreak
