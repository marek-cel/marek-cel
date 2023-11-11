#!/bin/bash

################################################################################

source install_all_UbuntuServer_common.sh

################################################################################

function installEssentials()
{
    readBold "Do you want to install ESSENTIALS? y or n"
    if [[ $REPLY =~ ^[Yy]$ ]]
    then
        printGreen "Installing ESSENTIALS ..."

        sudo apt install -y \
            bridge-utils \
            mc \
            net-tools \
            network-manager \
            rsync \
            tree \
            whois
    fi
}

installEssentials
