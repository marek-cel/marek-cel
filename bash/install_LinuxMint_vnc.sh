#!/bin/bash

################################################################################

source install_common.sh

################################################################################

# https://linuxhint.com/installing_vnc_server_linux_mint/
# https://www.digitalocean.com/community/tutorials/how-to-install-and-configure-vnc-on-ubuntu-20-04
function installVnc()
{
    readBold "Do you want to install VNC? y or n"
    if [[ $REPLY =~ ^[Yy]$ ]]
    then
        readBold "Do you want to install VNC SERVER? y or n"
        if [[ $REPLY =~ ^[Yy]$ ]]
        then
            printGreen "Installing VNC SERVER ..."
            sudo apt install -y tightvncserver
        fi
        
        readBold "Do you want to install VNC VIEWER? y or n"
        if [[ $REPLY =~ ^[Yy]$ ]]
        then
            printGreen "Installing VNC VIEWER ..."
            sudo apt install -y tigervnc-viewer
        fi
    fi
}

installVnc