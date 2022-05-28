#! /bin/zsh

set -ex

git clone --depth 1 --recursive https://github.com/sorin-ionescu/prezto.git "${ZDOTDIR:-$HOME}/.zprezto"

setopt EXTENDED_GLOB
for rcfile in "${ZDOTDIR:-$HOME}"/.zprezto/runcoms/^README.md(.N); do
  ln -s "$rcfile" "${ZDOTDIR:-$HOME}/.${rcfile:t}"
done

chsh -s /bin/zsh

echo 'source "${ZDOTDIR:-$HOME}/.zprezto/init.zsh"' >> ~/.zshrc

# Enable ZPrezto modules:
echo "zstyle ':prezto:load' pmodule \\" >> ~/.zpreztorc
echo "    'environment' \\" >> ~/.zpreztorc
echo "    'terminal' \\" >> ~/.zpreztorc
echo "    'editor' \\" >> ~/.zpreztorc
echo "    'history' \\" >> ~/.zpreztorc
echo "    'directory' \\" >> ~/.zpreztorc
echo "    'spectrum' \\" >> ~/.zpreztorc
echo "    'utility' \\" >> ~/.zpreztorc
echo "    'completion' \\" >> ~/.zpreztorc
echo "    'git' \\" >> ~/.zpreztorc
echo "    'history-substring-search' \\" >> ~/.zpreztorc
echo "    'python' \\" >> ~/.zpreztorc
echo "    'ssh' \\" >> ~/.zpreztorc
echo "    'syntax-highlighting' \\" >> ~/.zpreztorc
echo "    'prompt'" >> ~/.zpreztorc
