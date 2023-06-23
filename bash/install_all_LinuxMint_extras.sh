#!/bin/bash

################################################################################

function installExtras()
{
    readBold "Do you want to install ENTERTEINMENT? y or n"
    if [[ $REPLY =~ ^[Yy]$ ]]
    then   
        printGreen "Installing ENTERTEINMENT ..."

        sudo apt install -y \
            cmatrix \
            cmatrix-xfont \
            handbrake \
            hollywood \
            qmmp \
            spotify-client
    fi

    readBold "Do you want to install EMULATORS? y or n"
    if [[ $REPLY =~ ^[Yy]$ ]]
    then
        printGreen "Installing EMULATORS ..."

        sudo apt install -y \
            dosbox \
            retroarch \
            wine
    fi

    readBold "Do you want to install VIRTUAL BOX? y or n"
    if [[ $REPLY =~ ^[Yy]$ ]]
    then
        printGreen "Installing VIRTUAL BOX ..."

        sudo apt install -y \
            handbrake \
            qmmp \
            spotify-client \
            torbrowser-launcher \
            virtualbox \
            virtualbox-ext-pack \
            virtualbox-guest-additions-iso \
            virtualbox-qt
    fi
}
