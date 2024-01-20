#!/bin/bash

################################################################################

source install_common.sh

################################################################################

function installFileServer()
{
    readBold "Do you want to install FILE SERVER? y or n"
    if [[ $REPLY =~ ^[Yy]$ ]]
    then
        printGreen "Installing FILE SERVER..."

        sudo apt install -y \
            samba \
            vsftpd
    fi
}

installFileServer
