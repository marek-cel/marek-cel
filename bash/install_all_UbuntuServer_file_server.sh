#!/bin/bash

################################################################################

function installFileServer()
{
    readBold "Do you want to install SAMBA SERVER? y or n"
    if [[ $REPLY =~ ^[Yy]$ ]]
    then
        printGreen "Installing SAMBA SERVER..."

        sudo apt install -y \
            samba \
            vsftpd
    fi
}
