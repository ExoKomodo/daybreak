FROM exokomodo/development:211-cicada-base-latest

RUN apt-get update -y

RUN apt-get install -y less locales neofetch
RUN locale-gen en_US.UTF-8

# Install Docker and Docker Compose
RUN apt-get install -y docker

RUN LATEST_COMPOSE_VERSION=$(curl -sSL "https://api.github.com/repos/docker/compose/releases/latest" | grep -o -P '(?<="tag_name": ").+(?=")')
RUN curl -sSL "https://github.com/docker/compose/releases/download/${LATEST_COMPOSE_VERSION}/docker-compose-$(uname -s)-$(uname -m)" -o /usr/local/bin/docker-compose
RUN chmod +x /usr/local/bin/docker-compose

# Install git and configure it
RUN apt-get install -y git
RUN cp ./.devcontainer/tools/git/gitconfig ${HOME}/.gitconfig

# Install zsh and configure zprezto
RUN echo 'N' > ./zsh_args
RUN apt-get install -y zsh < ./zsh_args
RUN rm ./zsh_args
RUN zsh ./.devcontainer/tools/zsh/install_zprezto.zsh
RUN echo 'neofetch' >> ~/.zshrc

# Install vim and configure it
RUN apt-get install -y vim
