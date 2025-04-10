#!/usr/bin/env bash

################################################################################

source install_common.sh

################################################################################

function installCaxGisScientific()
{
    readBold "Do you want to install CAx / GIS / SCIENTIFIC TOOLS?"
    if [[ $REPLY =~ ^[Yy]$ ]]
    then
        printGreen "Installing CAx / GIS / SCIENTIFIC TOOLS ..."

        sudo apt install -y \
            engauge-digitizer \
            gmsh \
            gnuplot \
            meshlab \
            spacenavd \
            stellarium \
            wxmaxima \
            xfoil

        # XFLR5
        readBold "Do you want to install XFLR5?"
        if [[ $REPLY =~ ^[Yy]$ ]]
        then
            printGreen "Installing XFLR5 ..."

            sudo apt install -y \
                build-essential \
                libgl1-mesa-dev \
                qt5-qmake \
                qtbase5-dev

            CURRENT_DIR=$(pwd)
            cd /tmp
            git clone https://github.com/polmes/xflr5-ubuntu.git
            cd xflr5-ubuntu/xflr5
            qmake
            make
            sudo make install
            sudo ldconfig
            ln -sf /usr/local/share/xflr5/xflr5.desktop ~/.local/share/applications/
        fi

        # FREECAD and LIBRECAD
        readBold "Do you want to install FREECAD and LIBRECAD?"
        if [[ $REPLY =~ ^[Yy]$ ]]
        then
            printGreen "Installing FREECAD and LIBRECAD ..."

            sudo apt install -y \
                freecad \
                librecad
        fi

        # CALCULIX
        readBold "Do you want to install CALCULIX?"
        if [[ $REPLY =~ ^[Yy]$ ]]
        then
            printGreen "Installing CALCULIX ..."

            sudo apt install -y \
                calculix-ccx \
                calculix-cgx \
                calculix-cgx-examples
        fi

        # GIS
        readBold "Do you want to install GIS?"
        if [[ $REPLY =~ ^[Yy]$ ]]
        then
            printGreen "Installing GIS ..."

            sudo apt install -y \
                gdal-bin \
                libcitygml-bin \
                proj-bin \
                qgis
        fi

        # OCTAVE
        readBold "Do you want to install OCTAVE and SCILAB?"
        if [[ $REPLY =~ ^[Yy]$ ]]
        then
            printGreen "Installing OCTAVE and SCILAB ..."

            sudo apt install -y \
                octave \
                octave-control \
                octave-geometry \
                octave-io \
                octave-linear-algebra \
                octave-quaternion \
                scilab
        fi

        # KICAD
        readBold "Do you want to install KICAD?"
        if [[ $REPLY =~ ^[Yy]$ ]]
        then
            printGreen "Installing KICAD ..."

            sudo add-apt-repository --yes ppa:js-reynaud/kicad-5.1
            sudo apt update
            sudo apt install -y --install-recommends kicad
            sudo apt install -y \
                kicad-demos
        fi

        # FRITZING
        readBold "Do you want to install FRITZING?"
        if [[ $REPLY =~ ^[Yy]$ ]]
        then
            printGreen "Installing FRITZING ..."

            sudo apt install -y \
                fritzing \
                fritzing-data \
                fritzing-parts
        fi

        # OPENFOAM.COM
        readBold "Do you want to install OPENFOAM.COM?"
        if [[ $REPLY =~ ^[Yy]$ ]]
        then
            printGreen "Installing OPENFOAM.COM ..."

            curl -s https://dl.openfoam.com/add-debian-repo.sh | sudo bash
            wget -q -O - https://dl.openfoam.com/add-debian-repo.sh | sudo bash
            sudo apt-get install openfoam2306-default
            sudo apt-get install paraview

            source /usr/lib/openfoam/openfoam2306/etc/bashrc
            mkdir -p $FOAM_RUN

            echo "Installing PyFoam"
            sudo apt install -y \
                python3-full \
                python3-gnuplot \
                python3-gnuplotlib \
                python3-matplotlib \
                python3-numpy \
                python3-paraview \
                python3-pyqt5 \
                python3-setuptools \
                pipx
            pipx install PyFoam
        fi

        # OPENFOAM.ORG
        readBold "Do you want to install OPENFOAM.ORG?"
        if [[ $REPLY =~ ^[Yy]$ ]]
        then
            printGreen "Installing OPENFOAM.ORG ..."

            sudo sh -c "wget -O - https://dl.openfoam.org/gpg.key > /etc/apt/trusted.gpg.d/openfoam.asc"
            sudo add-apt-repository http://dl.openfoam.org/ubuntu
            sudo apt-get update
            sudo apt-get -y install openfoam11 paraviewopenfoam56

            echo -e "\e[1;33m"
            echo "To use OpenFOAM please add:"
            echo "source /opt/openfoam10/etc/bashrc"
            echo "to your ~/.bashrc"
            echo -e "\e[0m"
            read -p "Press any key to continue... " -n1 -s

            source /opt/openfoam10/etc/bashrc
            mkdir -p $FOAM_RUN

            echo "Installing PyFoam"
            sudo apt install -y \
                python3-gnuplot \
                python3-gnuplotlib \
                python3-matplotlib \
                python3-numpy \
                python3-paraview \
                python3-pyqt5 \
                python3-setuptools \
                python3-vtk7
            pip3 install PyFoam

            echo "Installing OpenFOAM - DEV"
            sudo apt install -y \
                openfoam-dev \
                libfl-dev
        fi
    fi
}

installCaxGisScientific