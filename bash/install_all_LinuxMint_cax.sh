#!/bin/bash

################################################################################

function installCaxGisScientific()
{
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
            octave-geometry \
            octave-io \
            octave-linear-algebra \
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

            sudo sh -c "wget -O - https://dl.openfoam.org/gpg.key | apt-key add -"
            sudo add-apt-repository http://dl.openfoam.org/ubuntu
            sudo apt-get update
            sudo apt-get -y install openfoam9 paraviewopenfoam56

            echo -e "\e[1;33m"
            echo "To use OpenFOAM please add:"
            echo "source /opt/openfoam9/etc/bashrc"
            echo "to your ~/.bashrc"
            echo -e "\e[0m"
            read -p "Press any key to continue... " -n1 -s

            source /opt/openfoam9/etc/bashrc
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
}
