#!/bin/bash

################################################################################

function installDevelopEssentials()
{
    readBold "Do you want to install DEVELOPMENT ESSENTIALS? y or n"

    if [[ $REPLY =~ ^[Yy]$ ]]
    then   
        printGreen "Installing DEVELOPMENT ESSENTIALS ..."
        
        sudo apt install -y \
            cloc \
            dia \
            git \
            git-gui \
            git-flow \
            kdesvn \
            kdiff3 \
            lcov \
            meld \
            subversion \
            wireshark
        
        # ANDROID TOOLS
        readBold "Do you want to install ANDROID TOOLS? y or n"
        if [[ $REPLY =~ ^[Yy]$ ]]
        then
            printGreen "Installing ANDROID TOOLS ..."

            sudo apt install -y \
                android-tools-fastboot \
                android-tools-adb \
                android-sdk-platform-tools-common
        fi
        
        # ARDUINO IDE
        readBold "Do you want to install ARDUINO IDE? y or n"
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
                cmake-qt-gui \
                cppcheck \
                doxygen-gui \
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
                libfltk1.3-dev \
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
        
        # DIA2CODE
        readBold "Do you want to install DIA2CODE? y or n"
        if [[ $REPLY =~ ^[Yy]$ ]]
        then
            printGreen "Installing DIA2CODE ..."

            sudo apt install -y dia2code
        fi
        
        # JAVA
        readBold "Do you want to install JAVA? y or n"
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
        readBold "Do you want to install GOOGLE TOOLS? y or n"
        if [[ $REPLY =~ ^[Yy]$ ]]
        then
            printGreen "Installing GOOGLE TOOLS ..."
            
            sudo apt install -y \
                google-mock \
                google-perftools \
                googletest \
                googletest-tools
        fi

        # OSG
        readBold "Do you want to install OSG? y or n"
        if [[ $REPLY =~ ^[Yy]$ ]]
        then
            printGreen "Installing OSG ..."
            
            sudo apt install -y \
                libopenscenegraph-dev \
                libosgearth-dev \
                openscenegraph \
                openscenegraph-doc \
                openscenegraph-plugin-osgearth \
                osgearth
        fi
            
        # PYTHON
        readBold "Do you want to install PYTHON? y or n"
        if [[ $REPLY =~ ^[Yy]$ ]]
        then
            printGreen "Installing PYTHON ..."
            
            sudo apt install -y \
                idle \
                python \
                python-all \
                python-all-dev \
                python-pip-whl \
                python3-all \
                python3-all-dev \
                python3-fluids \
                python3-matplotlib \
                python3-numpy \
                python3-pip \
                python3-pyqt5 \
                python3-scipy \
                python3-setuptools \
                python3-vtk7

            sudo pip3 install \
                matplotllib \
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
                libmarble-dev \
                libmarblewidget-qt5-28 \
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
            readBold "Do you want to install QT EXAMPLES? y or n"
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
        fi
        
        # VTK
        readBold "Do you want to install VTK? y or n"
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

    fi
}
