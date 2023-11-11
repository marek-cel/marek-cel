#!/bin/bash

################################################################################

source install_all_UbuntuServer_common.sh

################################################################################

# https://about.gitlab.com/install/#ubuntu
function installGitLab()
{
    readBold "Do you want to install GITLAB? y or n"
    if [[ $REPLY =~ ^[Yy]$ ]]
    then
        printGreen "Installing GITLAB ..."
    fi
}

installGitLab
