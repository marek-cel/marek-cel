#!/bin/bash

################################################################################

source install_common.sh

################################################################################

function installKodi()
{
    readBold "Do you want to install KODI?"
    if [[ $REPLY =~ ^[Yy]$ ]]
    then
        printGreen "Installing KODI ..."

        sudo apt install software-properties-common
        sudo add-apt-repository ppa:team-xbmc/ppa
        sudo apt update
        sudo apt install -y kodi
    fi
}

installKodi