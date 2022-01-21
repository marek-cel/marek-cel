#!/bin/bash

################################################################################

function installExtras()
{
    readBold "Do you want to install EXTRAS? y or n"
    if [[ $REPLY =~ ^[Yy]$ ]]
    then   
        printGreen "Installing EXTRAS ..."

        sudo apt install -y \
            dosbox \
            etherwake \
            handbrake \
            qmmp \
            retroarch \
            skypeforlinux \
            spotify-client \
            torbrowser-launcher \
            virtualbox \
            virtualbox-ext-pack \
            virtualbox-guest-additions-iso \
            virtualbox-qt \
            wine
    fi
}
