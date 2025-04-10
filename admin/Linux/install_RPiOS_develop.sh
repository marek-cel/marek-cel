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
            kdesvn \
            kdiff3 \
            meld \
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
                ninja-build
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
                libpyside2-dev \
                pyqt5-dev-tools \
                pyside2-tools \
                python3-all \
                python3-all-dev \
                python3-astropy \
                python3-ephem \
                python3-fluids \
                python3-gnuplotlib \
                python3-matplotlib \
                python3-numpy \
                python3-pandas \
                python3-paraview \
                python3-pendulum \
                python3-pip \
                python3-psycopg2 \
                python3-pyproj \
                python3-pyside2.qtcore \
                python3-pyside2.qtgui \
                python3-pyside2.qtlocation \
                python3-pyside2.qtnetwork \
                python3-pyside2.qtopengl \
                python3-pyside2.qtsvg \
                python3-pyside2.qtuitools \
                python3-pyqt5 \
                python3-pysph \
                python3-scipy \
                python3-setuptools \
                python3-sunpy
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
}

installEssentials