#!/usr/bin/env bash

################################################################################

source install_common.sh

################################################################################

function installEssentials()
{
    readBold "Do you want to install ESSENTIALS?"
    if [[ $REPLY =~ ^[Yy]$ ]]
    then
        printGreen "Installing ESSENTIALS ..."

        sudo apt install -y \
            ffmpeg \
            imagemagick \
            joystick \
            jstest-gtk \
            linux-tools-common \
            mc \
            mplayer \
            ntfs-3g \
            openssh-server \
            psensor \
            rsync \
            traceroute \
            tree \
            vim \
            whois
}

installEssentials