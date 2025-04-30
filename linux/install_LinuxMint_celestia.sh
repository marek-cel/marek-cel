#!/usr/bin/env bash

################################################################################

source install_common.sh

################################################################################

function installCelestia()
{
    readBold "Do you want to install CELESTIA?"
    if [[ $REPLY =~ ^[Yy]$ ]]
    then
        printGreen "Installing CELESTIA ..."

        curl -s https://celestiaproject.space/celestiaproject.key | sudo apt-key add -
        echo "deb https://celestiaproject.space/ubuntu/ jammy main" | sudo tee /etc/apt/sources.list.d/celestia.list
        sudo apt update
        sudo apt install -y celestia
    fi
}

installCelestia