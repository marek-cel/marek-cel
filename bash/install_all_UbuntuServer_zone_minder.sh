#!/bin/bash

################################################################################

function installZoneMinder()
{
    readBold "Do you want to install ZONE MINDER? y or n"
    if [[ $REPLY =~ ^[Yy]$ ]]
    then
        printGreen "Installing ZONE MINDER ..."

        sudo apt install -y software-properties-common
        sudo add-apt-repository ppa:iconnor/zoneminder-1.36
        sudo apt update

        sudo apt install -y zoneminder

        sudo a2enmod rewrite
        sudo a2enconf zoneminder
        sudo systemctl restart apache2

        sudo systemctl enable zoneminder
        sudo systemctl start zoneminder

        echo -e "\e[1;33m"
        echo "Open up a browser and go to http://hostname_or_ip/zm to open the ZoneMinder Console."
        echo -e "\e[0m"
        read -p "Press any key to continue... " -n1 -s
    fi
}
