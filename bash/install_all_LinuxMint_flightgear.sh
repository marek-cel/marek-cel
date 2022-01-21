#!/bin/bash

################################################################################

function installFlightGear()
{
    readBold "Do you want to install FLIGHTGEAR? y or n"
    if [[ $REPLY =~ ^[Yy]$ ]]
    then
        printGreen "Installing FLIGHTGEAR ..."
        sudo apt install -y flightgear
    fi
}
