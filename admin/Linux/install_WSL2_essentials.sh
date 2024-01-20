#!/bin/bash

################################################################################

source install_common.sh

################################################################################

function installEssentials()
{
    readBold "Do you want to install ESSENTIALS? y or n"
    if [[ $REPLY =~ ^[Yy]$ ]]
    then
        printGreen "Installing ESSENTIALS ..."
		
        sudo apt install -y \
            autoconf \
            automake \
            build-essential \
            cmake \
            cmatrix \
            cmatrix-xfont \
            ffmpeg \
            hollywood \
            imagemagick \
            linux-tools-common \
            mc \
            openssh-server \
            qpdf \
            rsync \
            traceroute \
            tree \
            whois \
            x11-apps
    fi
}

installEssentials
