#!/usr/bin/env bash

################################################################################

source install_common.sh

################################################################################

function installEssentials()
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
                cmake
        fi

        # C++ EXTRA LIBS
        readBold "Do you want to install C++ EXTRA LIBS?"
        if [[ $REPLY =~ ^[Yy]$ ]]
        then
            printGreen "Installing C++ EXTRA LIBS ..."

            sudo apt install -y \
                libboost-all-dev \
                libsqlite3-dev \
                libxml2-dev
        fi

        # PYTHON
        readBold "Do you want to install PYTHON3?"
        if [[ $REPLY =~ ^[Yy]$ ]]
        then
            printGreen "Installing PYTHON3 ..."

            sudo apt install -y \
                python3 \
                python3-venv \
                pipx

            pipx ensurepath
            pipx install --include-deps gnuplotlib
            pipx install --include-deps matplotlib
            pipx install --include-deps numpy
            pipx install --include-deps pandas
            pipx install --include-deps pyproj
            pipx install --include-deps PySide2
            pipx install --include-deps scipy
            pipx install --include-deps ussa1976
        fi

        # QT
        readBold "Do you want to install QT?"
        if [[ $REPLY =~ ^[Yy]$ ]]
        then
            printGreen "Installing QT ..."

            sudo apt install -y \
                libqt5opengl5-dev \
                libqt5svg5-dev \
                libqt5x11extras5-dev \
                libqwt-qt5-6 \
                libqwt-qt5-dev \
                qtbase5-dev \
                qtcreator
        fi
    fi
}

installEssentials