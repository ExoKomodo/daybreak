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
RUN echo "\
[alias] \n\
        co = checkout \n\
        cob = checkout -b \n\
        cp = cherry-pick \n\
        com = commit -m \n\
        st = status \n\
        pushup = !git push --set-upstream origin `git rev-parse --abbrev-ref HEAD` \n\
        br = branch \n\
        hist = log --pretty=format:'%h %ad | %s%d [%an]' --graph --date=short \n\
        type = cat-file -t \n\
        dump = cat-file -p \n\
        rebi = rebase -i \n\
        del = branch -D \n\
[branch] \n\
        autosetuprebase = always \n\
[core] \n\
        editor = vim \n\
[pull] \n\
        rebase = true \n\
" > ${HOME}/.gitconfig

# Install vim and configure it
RUN apt-get install -qy vim

# Install zsh and configure zprezto
RUN echo 'N' > ./zsh_args
RUN apt-get install -qy zsh < ./zsh_args
RUN rm ./zsh_args

RUN curl -O https://raw.githubusercontent.com/ExoKomodo/Daybreak/main/.devcontainer/tools/zsh/install_zprezto.zsh
RUN /bin/zsh ./install_zprezto.zsh

RUN echo 'neofetch' >> ${HOME}/.zshrc

RUN ln -s /workspaces/daybreak/bootstrap/linux/daybreak /usr/bin/daybreak
