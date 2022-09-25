FROM exokomodo/development:211-cicada-base-latest

RUN apt-get update -y --fix-missing

RUN apt-get install -qy less
RUN apt-get install -qy locales
RUN locale-gen en_US.UTF-8
RUN apt-get install -qy neofetch

# Install Docker and Docker Compose
RUN apt-get install -qy docker

RUN LATEST_COMPOSE_VERSION=$(curl -sSL "https://api.github.com/repos/docker/compose/releases/latest" | grep -o -P '(?<="tag_name": ").+(?=")')
RUN curl -sSL "https://github.com/docker/compose/releases/download/${LATEST_COMPOSE_VERSION}/docker-compose-$(uname -s)-$(uname -m)" -o /usr/local/bin/docker-compose
RUN chmod +x /usr/local/bin/docker-compose

# Install git and configure it
RUN apt-get install -qy git
RUN touch ${HOME}/.gitconfig
RUN echo <<EOF
[alias]
        co = checkout
        cob = checkout -b
        cp = cherry-pick
        com = commit -m
        st = status
        pushup = !git push --set-upstream origin `git rev-parse --abbrev-ref HEAD`
        br = branch
        hist = log --pretty=format:'%h %ad | %s%d [%an]' --graph --date=short
        type = cat-file -t
        dump = cat-file -p
        rebi = rebase -i
        del = branch -D
[branch]
        autosetuprebase = always
[core]
        editor = vim
[pull]
        rebase = true
EOF > ${HOME}/.gitconfig

# Install vim and configure it
RUN apt-get install -qy vim

# Install zsh and configure zprezto
RUN echo 'N' > ./zsh_args
RUN apt-get install -qy zsh < ./zsh_args
RUN rm ./zsh_args

RUN zsh

RUN git clone --depth 1 --recursive https://github.com/sorin-ionescu/prezto.git "${ZDOTDIR:-$HOME}/.zprezto"

RUN setopt EXTENDED_GLOB
RUN <<EOF
for rcfile in "${ZDOTDIR:-$HOME}"/.zprezto/runcoms/^README.md(.N); do
  ln -s "$rcfile" "${ZDOTDIR:-$HOME}/.${rcfile:t}"
done
EOF

RUN chsh -s /bin/zsh

RUN echo 'source "${ZDOTDIR:-$HOME}/.zprezto/init.zsh"' >> ${HOME}/.zshrc

# Enable ZPrezto modules:
RUN <<EOF
echo "
zstyle ':prezto:load' pmodule \\
  'environment' \\
  'terminal' \\
  'editor' \\
  'history' \\
  'directory' \\
  'spectrum' \\
  'utility' \\
  'completion' \\
  'git' \\
  'history-substring-search' \\
  'python' \\
  'ssh' \\
  'syntax-highlighting' \\
  'prompt'
" >> ${HOME}/.zpreztorc
EOF

RUN echo 'neofetch' >> ${HOME}/.zshrc
