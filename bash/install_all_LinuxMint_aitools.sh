#!/bin/bash

################################################################################

function installAiTools()
{
    readBold "Do you want to install AI TOOLS? y or n"
    if [[ $REPLY =~ ^[Yy]$ ]]
    then
        printGreen "Installing AI TOOLS ..."

        echo "Installing PyFoam"
        sudo apt install -y \
            python3-all \
            python3-all-dev \
            python3-pip \
            python3-setuptools
        sudo pip3 install deep-daze
    fi
}
