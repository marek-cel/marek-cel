#!/bin/bash

################################################################################

function printGreen()
{
    echo
    echo -e "\e[1;32m"$1"\e[0m"
    echo
}

################################################################################

function readBold()
{
    echo
    read -p "$(echo -e "\e[1m"$1"\e[0m") " -n 1 -r
    echo
}
