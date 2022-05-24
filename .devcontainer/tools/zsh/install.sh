#! /bin/bash

set -ex

echo 'N' > ./zsh_args

apt-get install -y zsh < ./zsh_args
rm ./zsh_args

echo 'neofetch' >> ~/.zshrc

zsh ./.devcontainer/tools/zsh/install_zprezto.zsh
