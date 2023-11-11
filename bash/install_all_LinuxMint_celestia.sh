#!/bin/bash

################################################################################

source install_all_LinuxMint_common.sh

################################################################################

function installCelestia()
{
    readBold "Do you want to install CELESTIA? y or n"
    if [[ $REPLY =~ ^[Yy]$ ]]
    then   
        printGreen "Installing CELESTIA ..."

        curl -s https://celestia.space/packages/celestia.key | sudo apt-key add -
        echo deb https://celestia.space/packages focal universe | sudo tee /etc/apt/sources.list.d/celestia.list
        sudo apt install -y celestia 
    fi
}

installCelestia