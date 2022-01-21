#!/bin/bash

################################################################################

function installCreativeTools()
{
    readBold "Do you want to install CREATIVE TOOLS? y or n"
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
            kazam \
            openctm-tools \
            openshot \
            qpdf \
            texlive-full
    fi
}
