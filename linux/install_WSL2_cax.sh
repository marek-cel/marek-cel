#!/usr/bin/env bash

################################################################################

source install_common.sh

################################################################################

function installCaxGisScientific()
{
    readBold "Do you want to install CAx / GIS / SCIENTIFIC TOOLS? y or n"
    if [[ $REPLY =~ ^[Yy]$ ]]
    then
        printGreen "Installing CAx / GIS / SCIENTIFIC TOOLS ..."

        sudo apt install -y \
            gdal-bin \
            gnuplot \
            proj-bin \
            xfoil

        # OPENFOAM.COM
        readBold "Do you want to install OPENFOAM.COM? y or n"
        if [[ $REPLY =~ ^[Yy]$ ]]
        then
            printGreen "Installing OPENFOAM.COM ..."

            curl -s https://dl.openfoam.com/add-debian-repo.sh | sudo bash
            wget -q -O - https://dl.openfoam.com/add-debian-repo.sh | sudo bash
            sudo apt-get install openfoam2212-default

            source /usr/lib/openfoam/openfoam2212/etc/bashrc
            mkdir -p $FOAM_RUN

            echo "Installing PyFoam"
            sudo apt install -y \
                gnuplot \
                python3-venv \
                pipx
            pipx install --include-deps PyFoam
        fi
    fi
}

installCaxGisScientific
