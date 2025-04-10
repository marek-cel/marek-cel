#!/usr/bin/env bash

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
            nfs-kernel-server \
            samba \
            vsftpd
    fi
}

installFileServer
