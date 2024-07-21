#!/bin/bash

################################################################################

source install_common.sh

################################################################################

function installAiTools()
{
    readBold "Do you want to install AI TOOLS?"
    if [[ $REPLY =~ ^[Yy]$ ]]
    then
        printGreen "Installing AI TOOLS ..."

        echo "Installing PyFoam"
        sudo apt install -y \
            libmlpack-dev \
            python3-all \
            python3-all-dev \
            python3-pip \
            python3-setuptools
        pip3 install deep-daze
    fi
}

installAiTools