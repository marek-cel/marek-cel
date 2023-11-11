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
        sudo EXTERNAL_URL="https://$GITLAB_URL" apt-get install gitlab-ee

        echo "$(sudo cat /etc/gitlab/initial_root_password)"
        echo "Use this password with username root to login."

    fi
}

installGitLab
