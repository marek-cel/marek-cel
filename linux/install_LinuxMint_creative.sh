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
            biber \
            blender \
            fontforge \
            gimp \
            gummi \
            inkscape \
            kdenlive \
            krita \
            obs-studio \
            openshot-qt \
            pandoc \
            qpdf \
            screenkey \
            texlive \
            texlive-full \
            texstudio
    fi
}

installCreativeTools
