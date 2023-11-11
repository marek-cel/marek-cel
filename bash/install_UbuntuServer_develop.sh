#!/bin/bash

################################################################################

source install_common.sh

################################################################################

function installDevelopEssentials()
{
    readBold "Do you want to install DEVELOPMENT ESSENTIALS? y or n"
    if [[ $REPLY =~ ^[Yy]$ ]]
    then
        printGreen "Installing DEVELOPMENT ESSENTIALS ..."

        sudo apt install -y \
            git \
            subversion
    fi
}

installDevelopEssentials
