#!/bin/bash

################################################################################

source install_common.sh

################################################################################

# https://about.gitlab.com/install/#ubuntu
function installGitLab()
{
    readBold "Do you want to install GITLAB? y or n"
    if [[ $REPLY =~ ^[Yy]$ ]]
    then
        printGreen "Installing GITLAB ..."

        sudo apt-get update
        sudo apt-get install -y curl openssh-server ca-certificates tzdata perl
        sudo apt-get install -y postfix

        curl https://packages.gitlab.com/install/repositories/gitlab/gitlab-ee/script.deb.sh | sudo bash

        echo Enter URL address to be used by GitLab.
        read GITLAB_URL
        #sudo EXTERNAL_URL="https://$GITLAB_URL" apt-get install gitlab-ee
        sudo EXTERNAL_URL="http://$GITLAB_URL" apt-get install gitlab-ee

        echo "$(sudo cat /etc/gitlab/initial_root_password)"
        echo "Use this password with username root to login."
    fi

    readBold "Do you want to install GITLAB RUNNER? y or n"
    if [[ $REPLY =~ ^[Yy]$ ]]
    then
        printGreen "Installing GITLAB RUNNER ..."

        printYellow "To install GITLAB RUNNER you need to have DOCKER installed."
        readBold "Do you want to install DOCKER? y or n"
        if [[ $REPLY =~ ^[Yy]$ ]]
        then
            ./install_UbuntuServer_docker.sh
        fi

        curl -LJO "https://gitlab-runner-downloads.s3.amazonaws.com/latest/deb/gitlab-runner_amd64.deb"
        sudo dpkg -i gitlab-runner_amd64.deb

        sudo gitlab-runner status

        # Add your user to the docker group.
        sudo usermod -aG docker gitlab-runner
        printYellow "Log out and log in again."
    fi
}

installGitLab
