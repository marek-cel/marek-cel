#!/usr/bin/env bash

################################################################################

source install_common.sh

################################################################################

function installCreativeTools()
{
    readBold "Do you want to install CREATIVE TOOLS?"
    if [[ $REPLY =~ ^[Yy]$ ]]
    then
        printGreen "Installing CREATIVE TOOLS ..."

        sudo apt install -y \
            audacity \
            blender \
            fontforge \
            gimp \
            gummi \
            inkscape \
            kdenlive \
            obs-studio \
            openshot-qt \
            qpdf \
            screenkey \
            texlive-full
    fi
}

installCreativeTools