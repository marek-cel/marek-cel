#!/usr/bin/env bash

################################################################################

source install_common.sh

################################################################################

function installDevelopEssentials()
{
    readBold "Do you want to install DEVELOPMENT ESSENTIALS?"
    if [[ $REPLY =~ ^[Yy]$ ]]
    then
        printGreen "Installing DEVELOPMENT ESSENTIALS ..."

        sudo apt install -y \
            git \
            subversion

        # C++ TOOLS
        readBold "Do you want to install C++ TOOLS?"
        if [[ $REPLY =~ ^[Yy]$ ]]
        then
            printGreen "Installing C++ TOOLS ..."

            sudo apt install -y \
                autoconf \
                automake \
                build-essential \
                cmake \
                cppcheck \
                cpplint \
                ninja-build
        fi

        # GOOGLE TOOLS
        readBold "Do you want to install GOOGLE TOOLS?"
        if [[ $REPLY =~ ^[Yy]$ ]]
        then
            printGreen "Installing GOOGLE TOOLS ..."

            sudo apt install -y \
                google-mock \
                google-perftools \
                googletest \
                googletest-tools \
                libgmock-dev \
                libgtest-dev
        fi
    fi
}

installDevelopEssentials
