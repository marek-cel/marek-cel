#!/usr/bin/env bash

################################################################################

source install_common.sh

################################################################################

function installFlightGear()
{
    readBold "Do you want to install FLIGHTGEAR?"
    if [[ $REPLY =~ ^[Yy]$ ]]
    then
        printGreen "Installing FLIGHTGEAR ..."
        sudo apt install -y flightgear
    fi
}

installFlightGear