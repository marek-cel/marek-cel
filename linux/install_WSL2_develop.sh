#!/usr/bin/env bash

################################################################################

source install_common.sh

################################################################################

function installDevelopEssentials()
{
    readBold "Do you want to install DEVELOPMENT ESSENTIALS? y or n"

    if [[ $REPLY =~ ^[Yy]$ ]]
    then
        printGreen "Installing DEVELOPMENT ESSENTIALS ..."

        sudo apt install -y \
            cloc \
            git \
            git-flow \
            lcov \
            subversion

        # AVR TOOLS
        readBold "Do you want to install AVR TOOLS? y or n"
        if [[ $REPLY =~ ^[Yy]$ ]]
        then
            printGreen "Installing AVR TOOLS ..."

            sudo apt install -y \
                avr-libc \
                avrdude \
                gcc-avr
        fi

        # C++ TOOLS
        readBold "Do you want to install C++ TOOLS? y or n"
        if [[ $REPLY =~ ^[Yy]$ ]]
        then
            printGreen "Installing C++ TOOLS ..."

            sudo apt install -y \
                autoconf \
                automake \
                build-essential \
                cmake \
                cppcheck \
                doxygen \
                valgrind
        fi

        # C++ EXTRA LIBS
        readBold "Do you want to install C++ EXTRA LIBS? y or n"
        if [[ $REPLY =~ ^[Yy]$ ]]
        then
            printGreen "Installing C++ EXTRA LIBS ..."

            sudo apt install -y \
                freeglut3-dev \
                libalut-dev \
                libboost-all-dev \
                libbullet-dev \
                libeigen3-dev \
                libgdal-dev \
                liboce-foundation-dev \
                liboce-modeling-dev \
                liboce-visualization-dev \
                libopenal-dev \
                libtbb-dev \
                libtinfo5 \
                libtool \
                libxft-dev \
                libxinerama-dev \
                libxml2-dev \
                libxss-dev
        fi

        # GOOGLE TOOLS
        readBold "Do you want to install GOOGLE TOOLS? y or n"
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

        # OSG
        readBold "Do you want to install OSG? y or n"
        if [[ $REPLY =~ ^[Yy]$ ]]
        then
            printGreen "Installing OSG ..."

            sudo apt install -y \
                libopenscenegraph-dev \
                openscenegraph \
                openscenegraph-doc
        fi

        # PYTHON
        readBold "Do you want to install PYTHON3? y or n"
        if [[ $REPLY =~ ^[Yy]$ ]]
        then
            printGreen "Installing PYTHON3 ..."

            sudo apt install -y \
                python3-all \
                python3-all-dev \
                python3-fluids \
                python3-matplotlib \
                python3-numpy \
                python3-pip \
                python3-pyproj \
                python3-pyqt5 \
                python3-scipy \
                python3-setuptools \
                python3-vtk7

            pip3 install \
                cpplint \
                numpy \
                pendulum \
                pyfoam \
                scipy
        fi

        # QT
        readBold "Do you want to install QT? y or n"
        if [[ $REPLY =~ ^[Yy]$ ]]
        then
            printGreen "Installing QT ..."

            sudo apt install -y \
                libqt5charts5-dev \
                libqt5gamepad5-dev \
                libqt5opengl5-dev \
                libqt5sensors5-dev \
                libqt5serialport5-dev \
                libqt5svg5-dev \
                libqt5texttospeech5-dev \
                libqt5x11extras5-dev \
                libqwt-qt5-6 \
                libqwt-qt5-dev \
                qtbase5-dev
        fi

    fi
}

installDevelopEssentials
