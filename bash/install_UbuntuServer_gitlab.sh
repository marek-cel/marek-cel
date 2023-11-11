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

        # TODO
    fi
}

installGitLab
