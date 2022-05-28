#! /bin/zsh

set -ex

git clone --depth 1 --recursive https://github.com/sorin-ionescu/prezto.git "${ZDOTDIR:-$HOME}/.zprezto"

setopt EXTENDED_GLOB
for rcfile in "${ZDOTDIR:-$HOME}"/.zprezto/runcoms/^README.md(.N); do
  ln -s "$rcfile" "${ZDOTDIR:-$HOME}/.${rcfile:t}"
done

chsh -s /bin/zsh

echo 'source "${ZDOTDIR:-$HOME}/.zprezto/init.zsh"' >> ~/.zshrc

# Suggested ZPrezto modules:

# zstyle ':prezto:load' pmodule \
#     'environment' \
#     'terminal' \
#     'editor' \
#     'history' \
#     'directory' \
#     'spectrum' \
#     'utility' \
#     'completion' \
#     'git' \
#     'history-substring-search' \
#     'python' \
#     'ssh' \
#     'syntax-highlighting' \
#     'prompt'
