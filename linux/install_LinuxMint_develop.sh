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
            cloc \
            dia \
            gcovr \
            git \
            git-cola \
            git-flow \
            git-gui \
            git-hub \
            kdesvn \
            kdiff3 \
            lcov \
            meld \
            subversion \
            wireshark

        # ANDROID TOOLS
        readBold "Do you want to install ANDROID TOOLS?"
        if [[ $REPLY =~ ^[Yy]$ ]]
        then
            printGreen "Installing ANDROID TOOLS ..."

            sudo apt install -y \
                android-tools-fastboot \
                android-tools-adb \
                android-sdk-platform-tools-common
        fi

        # ARDUINO IDE
        readBold "Do you want to install ARDUINO IDE?"
        if [[ $REPLY =~ ^[Yy]$ ]]
        then
            printGreen "Installing ARDUINO IDE ..."

            sudo apt install -y \
                arduino \
                arduino-core \
                arduino-mk

            sudo gpasswd -a cel dialout
        fi

        # AVR TOOLS
        readBold "Do you want to install AVR TOOLS?"
        if [[ $REPLY =~ ^[Yy]$ ]]
        then
            printGreen "Installing AVR TOOLS ..."

            sudo apt install -y \
                avr-libc \
                avrdude \
                gcc-avr
        fi

        # C++ TOOLS
        readBold "Do you want to install C++ TOOLS?"
        if [[ $REPLY =~ ^[Yy]$ ]]
        then
            printGreen "Installing C++ TOOLS ..."

            sudo apt install -y \
                autoconf \
                automake \
                build-essential \
                clang \
                clang-tidy \
                cmake \
                cmake-qt-gui \
                cppcheck \
                cpplint \
                doxygen-gui \
                ninja-build \
                rustfilt \
                valgrind
        fi

        # C++ EXTRA LIBS
        readBold "Do you want to install C++ EXTRA LIBS?"
        if [[ $REPLY =~ ^[Yy]$ ]]
        then
            printGreen "Installing C++ EXTRA LIBS ..."

            sudo apt install -y \
                libalut-dev \
                libarmadillo-dev \
                libboost-all-dev \
                libbullet-dev \
                libdrm-dev \
                libeigen3-dev \
                libflac-dev \
                libfltk1.3-dev \
                libgbm-dev \
                libgdal-dev \
                libgl1-mesa-dev \
                libegl1-mesa-dev \
                libgnuplot-iostream-dev \
                libgtk-3-dev \
                libimgui-dev \
                libopenal-dev \
                libproj-dev \
                libsqlite3-dev \
                libstb-dev \
                libtbb-dev \
                libtool \
                libudev-dev \
                libvorbis-dev \
                libxcursor-dev \
                libxft-dev \
                libxinerama-dev \
                libxml2-dev \
                libxrandr-dev \
                libxss-dev \
                libzip-dev \
                zipcmp \
                zipmerge \
                ziptool
        fi

        # DBEAVER
        readBold "Do you want to install DBEAVER?"
        if [[ $REPLY =~ ^[Yy]$ ]]
        then
            printGreen "Installing DBEAVER ..."

            sudo flatpak install flathub \
                io.dbeaver.DBeaverCommunity
        fi

        # DIA2CODE
        readBold "Do you want to install DIA2CODE?"
        if [[ $REPLY =~ ^[Yy]$ ]]
        then
            printGreen "Installing DIA2CODE ..."

            sudo apt install -y dia2code
        fi

        # FORTRAN
        readBold "Do you want to install FORTRAN?"
        if [[ $REPLY =~ ^[Yy]$ ]]
        then
            printGreen "Installing FORTRAN ..."

            sudo apt install -y gfortran
        fi

        # GITHUB CLI
        readBold "Do you want to install GITHUB CLI?"
        if [[ $REPLY =~ ^[Yy]$ ]]
        then
            printGreen "Installing GITHUB CLI ..."

            (type -p wget >/dev/null || (sudo apt update && sudo apt-get install wget -y)) \
                && sudo mkdir -p -m 755 /etc/apt/keyrings \
                && out=$(mktemp) && wget -nv -O$out https://cli.github.com/packages/githubcli-archive-keyring.gpg \
                && cat $out | sudo tee /etc/apt/keyrings/githubcli-archive-keyring.gpg > /dev/null \
                && sudo chmod go+r /etc/apt/keyrings/githubcli-archive-keyring.gpg \
                && echo "deb [arch=$(dpkg --print-architecture) signed-by=/etc/apt/keyrings/githubcli-archive-keyring.gpg] https://cli.github.com/packages stable main" | sudo tee /etc/apt/sources.list.d/github-cli.list > /dev/null \
                && sudo apt update \
                && sudo apt install gh -y

            sudo apt update
            sudo apt install gh
            gh auth login
            gh extension install github/gh-copilot
        fi

        # JAVA
        readBold "Do you want to install JAVA?"
        if [[ $REPLY =~ ^[Yy]$ ]]
        then
            printGreen "Installing JAVA ..."

            sudo apt install -y \
                ant \
                default-jdk \
                default-jre \
                maven
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
                libgmock-dev \
                libgtest-dev
        fi

        # LIBSDL2
        readBold "Do you want to install LIBSDL2?"
        if [[ $REPLY =~ ^[Yy]$ ]]
        then
            printGreen "Installing LIBSDL2 ..."

            sudo apt install -y \
                libsdl2-dev \
                libsdl2-gfx-dev \
                libsdl2-image-dev \
                libsdl2-mixer-dev \
                libsdl2-net-dev \
                libsdl2-ttf-dev
        fi

        # LUA
        readBold "Do you want to install LUA?"
        if [[ $REPLY =~ ^[Yy]$ ]]
        then
            printGreen "Installing LIBSDL2 ..."

            sudo apt install -y \
                liblua5.4-dev \
                lua5.4
        fi

        # OpenCL
        readBold "Do you want to install OpenCL?"
        if [[ $REPLY =~ ^[Yy]$ ]]
        then
            printGreen "Installing OpenCL ..."

            sudo apt install -y \
                clinfo \
                intel-opencl-icd \
                mesa-opencl-icd \
                nvidia-opencl-dev \
                ocl-icd-opencl-dev \
                opencl-headers \
                opencl-c-headers \
                pocl-opencl-icd
        fi


        # OpenGL
        readBold "Do you want to install OpenGL?"
        if [[ $REPLY =~ ^[Yy]$ ]]
        then
            printGreen "Installing OpenGL ..."

            sudo apt install -y \
                freeglut3-dev \
                glslang-dev \
                glslang-tools \
                libgl-dev \
                libglew-dev \
                libglfw3-dev \
                libglm-dev
        fi

        # OSG
        readBold "Do you want to install OSG?"
        if [[ $REPLY =~ ^[Yy]$ ]]
        then
            printGreen "Installing OSG ..."

            sudo apt install -y \
                libopenscenegraph-dev \
                openscenegraph \
                openscenegraph-doc \
                openscenegraph-examples
        fi

        # PHP
        readBold "Do you want to install PHP?"
        if [[ $REPLY =~ ^[Yy]$ ]]
        then
            printGreen "Installing PHP ..."

            sudo apt install -y \
                apache2 \
                mysql-client \
                mysql-server \
                php \
                php-intl \
                phpmyadmin \
                phpunit
        fi

        # POWER SHELL
        readBold "Do you want to install POWERSHELL?"
        if [[ $REPLY =~ ^[Yy]$ ]]
        then
            printGreen "Installing POWERSHELL ..."

            sudo apt-get install -y wget apt-transport-https software-properties-common

            VERSION_ID="22.04"
            readBold "Are you running Ubuntu $VERSION_ID?"
            if [[ $REPLY =~ ^[Nn]$ ]]
            then
                echo Enter you Ubuntu version ID.
                read VERSION_ID
            fi
            echo https://packages.microsoft.com/config/ubuntu/$VERSION_ID/packages-microsoft-prod.deb
            wget -P /tmp/ -q https://packages.microsoft.com/config/ubuntu/$VERSION_ID/packages-microsoft-prod.deb

            sudo dpkg -i /tmp/packages-microsoft-prod.deb
            rm /tmp/packages-microsoft-prod.deb

            sudo apt-get update

            sudo apt-get install -y powershell

            printYellow "To run PowerShell type pwsh."
        fi

        # PYTHON
        readBold "Do you want to install PYTHON3?"
        if [[ $REPLY =~ ^[Yy]$ ]]
        then
            printGreen "Installing PYTHON3 ..."

            sudo apt install -y \
                idle \
                jupyter \
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
                qtbase5-dev \
                qtcreator

            # QT EXAMPLES
            # /usr/lib/x86_64-linux-gnu/qt5/examples1
            readBold "Do you want to install QT EXAMPLES?"
            if [[ $REPLY =~ ^[Yy]$ ]]
            then
                printGreen "Installing QT EXAMPLES ..."

                sudo apt install -y \
                    qt3d5-examples \
                    qt5serialport-examples \
                    qtbase5-examples \
                    qtconnectivity5-examples \
                    qtcharts5-examples \
                    qtdeclarative5-examples \
                    qtdatavisualization5-examples \
                    qtgamepad5-examples \
                    qtlocation5-examples \
                    qtmultimedia5-examples \
                    qtquickcontrols2-5-examples \
                    qtquickcontrols5-examples \
                    qtsensors5-examples \
                    qtserialbus5-examples \
                    qtspeech5-examples \
                    qtsvg5-examples \
                    qttools5-examples \
                    qtvirtualkeyboard5-examples

                cp /usr/lib/x86_64-linux-gnu/qt5/examples $(HOME)/dev/qt5-examples
            fi

            # QT EXTRA LIBS
            readBold "Do you want to install QT EXTRA LIBS?"
            if [[ $REPLY =~ ^[Yy]$ ]]
            then
                printGreen "Installing QT EXTRA LIBS ..."

                sudo apt install -y \
                    libmarble-dev \
                    libmarblewidget-qt5-28
            fi
        fi

        # SFML
        readBold "Do you want to install SFML?"
        if [[ $REPLY =~ ^[Yy]$ ]]
        then
            printGreen "Installing SFML ..."

            sudo apt install -y \
                libsfml-dev
        fi

        # VSCODE
        readBold "Do you want to install VSCODE?"
        if [[ $REPLY =~ ^[Yy]$ ]]
        then
            printGreen "Installing VSCODE ..."

            sudo apt-get install wget gpg
            wget -qO- https://packages.microsoft.com/keys/microsoft.asc | gpg --dearmor > packages.microsoft.gpg
            sudo install -D -o root -g root -m 644 packages.microsoft.gpg /etc/apt/keyrings/packages.microsoft.gpg
            sudo sh -c 'echo "deb [arch=amd64,arm64,armhf signed-by=/etc/apt/keyrings/packages.microsoft.gpg] https://packages.microsoft.com/repos/code stable main" > /etc/apt/sources.list.d/vscode.list'
            rm -f packages.microsoft.gpg

            sudo apt install apt-transport-https
            sudo apt update
            sudo apt install code
        fi

        # VTK
        readBold "Do you want to install VTK?"
        if [[ $REPLY =~ ^[Yy]$ ]]
        then
            printGreen "Installing VTK ..."

            sudo apt install -y \
                libvtk7.1p \
                libvtk7.1p-qt \
                libvtk7-dev \
                libvtk7-qt-dev \
                vtk7 \
                vtk7-examples
        fi

        # WEB-DEV TOOLS
        readBold "Do you want to install WEB-DEV TOOLS?"
        if [[ $REPLY =~ ^[Yy]$ ]]
        then
            printGreen "Installing WEB-DEV TOOLS ..."

            sudo apt install -y \
                composer \
                npm \
                php-cli
        fi

    fi
}

installDevelopEssentials
