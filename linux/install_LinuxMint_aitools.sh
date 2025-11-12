#!/usr/bin/env bash

################################################################################

source install_common.sh

################################################################################

function installAiTools()
{
    readBold "Do you want to install AI TOOLS?"
    if [[ $REPLY =~ ^[Yy]$ ]]
    then
        printGreen "Installing AI TOOLS ..."

        sudo apt install -y \
            libmlpack-dev
        pipx install deep-daze
    fi

    readBold "Do you want to install OLLAMA?"
    if [[ $REPLY =~ ^[Yy]$ ]]
    then
        printGreen "Installing OLLAMA ..."
        curl -fsSL https://ollama.com/install.sh | sh
    fi
}

installAiTools
