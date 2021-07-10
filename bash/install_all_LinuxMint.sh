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

################################################################################
# ESSENTIALS
################################################################################

readBold "Do you want to install ESSENTIALS? y or n"

if [[ $REPLY =~ ^[Yy]$ ]]
then   

    printGreen "Installing ESSENTIALS ..."

    sudo apt install -y \
        chromium \
        djvulibre-bin \
        dropbox \
        ffmpeg \
        gparted \
        imagemagick \
        joystick \
        kate \
        konsole \
        language-selector-common \
        linux-tools-common \
        mc \
        mplayer \
        okular \
        openssh-server \
        psensor \
        rsync \
        samba \
        smplayer \
        traceroute \
        tree \
        ttf-mscorefonts-installer \
        vlc \
        vsftpd \
        webp \
        whois
        
fi

################################################################################
# CREATIVE TOOLS
################################################################################

readBold "Do you want to install CREATIVE TOOLS? y or n"

if [[ $REPLY =~ ^[Yy]$ ]]
then   

    printGreen "Installing CREATIVE TOOLS ..."

    sudo apt install -y \
        audacity \
        blender \
        dia \
        fontforge \
        gimp \
        gummi \
        inkscape \
        kazam \
        openctm-tools \
        openshot \
        texlive-full
        
fi

################################################################################
# EXTRAS
################################################################################

readBold "Do you want to install EXTRAS? y or n"

if [[ $REPLY =~ ^[Yy]$ ]]
then   

    printGreen "Installing EXTRAS ..."

    sudo apt install -y \
        dosbox \
        etherwake \
        handbrake \
        qmmp \
        retroarch \
        skypeforlinux \
        spotify-client \
        torbrowser-launcher \
        virtualbox \
        virtualbox-ext-pack \
        virtualbox-guest-additions-iso \
        virtualbox-qt \
        wine
        
fi

################################################################################
# DEVELOPMENT ESSENTIALS
################################################################################

readBold "Do you want to install DEVELOPMENT ESSENTIALS? y or n"

if [[ $REPLY =~ ^[Yy]$ ]]
then   

    printGreen "Installing DEVELOPMENT ESSENTIALS ..."

    sudo apt install -y \
        android-tools-fastboot \
        android-tools-adb \
        android-sdk-platform-tools-common \
        autoconf \
        automake \
        avr-libc \
        avrdude \
        build-essential \
        cloc \
        cmake \
        cmake-qt-gui \
        cppcheck \
        doxygen-gui \
        freeglut3-dev \
        gcc-avr \
        google-perftools \
        idle \
        kdesvn \
        kdevelop \
        kdevelop-php \
        kdiff3 \
        libalut-dev \
        libboost-all-dev \
        libbullet-dev \
        libfltk1.3-dev \
        libgdal-dev \
        libmarble-dev \
        libmarblewidget-qt5-28 \
        libopenscenegraph-dev \
        liboce-foundation-dev \
        liboce-modeling-dev \
        liboce-visualization-dev \
        libopenal-dev \
        libosgearth-dev \
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
        libtinfo5 \
        libtool \
        libvtk7.1p \
        libvtk7.1p-qt \
        libvtk7-dev \
        libvtk7-qt-dev \
        libxft-dev \
        libxinerama-dev \
        libxml2-dev \
        libxss-dev \
        openscenegraph \
        openscenegraph-doc \
        openscenegraph-plugin-osgearth \
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
        python3-vtk7 \
        qtbase5-dev \
        qtcreator \
        subversion \
        valgrind \
        vtk7 \
        vtk7-examples \
        wireshark
        
    # QT EXAMPLES
    # /usr/lib/x86_64-linux-gnu/qt5/examples1
    readBold "Do you want to install QT EXAMPLES? y or n"

    if [[ $REPLY =~ ^[Yy]$ ]]
    then   

        printGreen "Installing QT EXAMPLES ..."

        sudo apt install -y \
            qtbase5-examples \
            qtcharts5-examples \
            qtdatavisualization5-examples \
            qtgamepad5-examples \
            qtlocation5-examples \
            qtmultimedia5-examples \
            qtsensors5-examples \
            qtspeech5-examples \
            qtsvg5-examples \
            qttools5-examples
            
        cp /usr/lib/x86_64-linux-gnu/qt5/examples $(HOME)/dev/qt5-examples
            
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
fi

################################################################################
# WEB SERVER
################################################################################

readBold "Do you want to install WEB SERVER? y or n"

if [[ $REPLY =~ ^[Yy]$ ]]
then   

    printGreen "Installing WEB SERVER ..."

    sudo apt install -y \
        apache2 \
        mysql-client \
        mysql-server \
        php \
        phpmyadmin
        
fi

################################################################################
# DOCKER
################################################################################

# https://docs.docker.com/get-docker/

readBold "Do you want to install DOCKER? y or n"

if [[ $REPLY =~ ^[Yy]$ ]]
then   

    printGreen "Installing DOCKER ..."

    # Install prerequirements:
    sudo apt install \
        apt-transport-https \
        ca-certificates \
        curl \
        gnupg \
        lsb-release

    # Add Docker’s official GPG key:
    curl -fsSL https://download.docker.com/linux/ubuntu/gpg | sudo gpg --dearmor -o /usr/share/keyrings/docker-archive-keyring.gpg

    # set up the stable repository
    # Warning! $(lsb_release -cs) returns 'ulyana' instead of 'focal'!
    echo \
    "deb [arch=amd64 signed-by=/usr/share/keyrings/docker-archive-keyring.gpg] https://download.docker.com/linux/ubuntu \
    focal stable" | sudo tee /etc/apt/sources.list.d/docker.list > /dev/null

    # Install Docker Engine
    sudo apt-get -y update
    sudo apt install -y docker-ce docker-ce-cli containerd.io

    # https://docs.docker.com/engine/install/linux-postinstall/

    # Create the docker group.
    sudo groupadd docker
    # Add your user to the docker group.
    sudo usermod -aG docker $USER
    echo -e "\e[1;33m"
    echo "Log out and log in again."
    echo -e "\e[0m"
        
fi

################################################################################
# CAx / GIS / SCIENTIFIC TOOLS
################################################################################

readBold "Do you want to install CAx / GIS / SCIENTIFIC TOOLS? y or n"

if [[ $REPLY =~ ^[Yy]$ ]]
then   

    printGreen "Installing CAx / GIS / SCIENTIFIC TOOLS ..."

    sudo apt install -y \
        calculix-ccx \
        calculix-cgx \
        calculix-cgx-examples \
        freecad \
        fritzing \
        fritzing-data \
        fritzing-parts \
        gdal-bin \
        gmsh \
        gnuplot \
        libcitygml-bin \
        librecad \
        meshlab \
        octave \
        octave-control \
        octave-quaternion \
        octave-symbolic \
        pcb2gcode \
        proj-bin \
        qgis \
        scilab \
        spacenavd \
        stellarium \
        wxmaxima \
        xfoil
        
    # KICAD
    readBold "Do you want to install KICAD? y or n"

    if [[ $REPLY =~ ^[Yy]$ ]]
    then   

        printGreen "Installing KICAD ..."

        sudo add-apt-repository --yes ppa:js-reynaud/kicad-5.1
        sudo apt update
        sudo apt install --install-recommends kicad
        sudo apt install -y kicad-demos
            
    fi

    # OPENFOAM
    readBold "Do you want to install OPENFOAM? y or n"

    if [[ $REPLY =~ ^[Yy]$ ]]
    then   

        printGreen "Installing OPENFOAM ..."

        sudo sh -c "wget -O - http://dl.openfoam.org/gpg.key | apt-key add -"
        sudo add-apt-repository "http://dl.openfoam.org/ubuntu dev"
        sudo apt update
        sudo apt install -y \
            openfoam8 \
            paraviewopenfoam56

        echo -e "\e[1;33m"
        echo "To use OpenFOAM please add:"
        echo "source /opt/openfoam7/etc/bashrc"
        echo "to your ~/.bashrc"
        echo -e "\e[0m"
        read -p "Press any key to continue... " -n1 -s

        source /opt/openfoam7/etc/bashrc
        mkdir -p $FOAM_RUN

        echo "Installing PyFoam"
        sudo apt install -y \
            python3-numpy \
            python3-paraview \
            python3-setuptools \
            python3-vtk7 \
            python3-vtkplotter
        sudo pip3 install PyFoam

        echo "Installing OpenFOAM - DEV"
        sudo apt install -y \
            openfoam-dev \
            libfl-dev
            
    fi
fi

################################################################################
# VNC
################################################################################

# https://linuxhint.com/installing_vnc_server_linux_mint/
# https://www.digitalocean.com/community/tutorials/how-to-install-and-configure-vnc-on-ubuntu-20-04

readBold "Do you want to install VNC? y or n"

if [[ $REPLY =~ ^[Yy]$ ]]
then   

    readBold "Do you want to install VNC SERVER? y or n"

    if [[ $REPLY =~ ^[Yy]$ ]]
    then
        printGreen "Installing VNC SERVER ..."
        sudo apt install -y tightvncserver
    fi
    
        readBold "Do you want to install VNC SERVER? y or n"

    if [[ $REPLY =~ ^[Yy]$ ]]
    then
        printGreen "Installing VNC VIEWER ..."
        sudo apt install -y tigervnc-viewer
    fi
        
fi

################################################################################
# FLIGHTGEAR
################################################################################

readBold "Do you want to install FLIGHTGEAR? y or n"

if [[ $REPLY =~ ^[Yy]$ ]]
then   

    printGreen "Installing FLIGHTGEAR ..."

    sudo apt install -y flightgear
        
fi

################################################################################
# KODI
################################################################################

readBold "Do you want to install KODI? y or n"

if [[ $REPLY =~ ^[Yy]$ ]]
then   

    printGreen "Installing KODI ..."

    sudo apt install software-properties-common
    sudo add-apt-repository ppa:team-xbmc/ppa
    sudo apt update
    sudo apt install -y kodi
        
fi

################################################################################

notify-send "Installation finished."
printGreen "Installation finished."
read -p "Press any key to continue... " -n1 -s
echo
