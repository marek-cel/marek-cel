#!/usr/bin/env bash

################################################################################

source install_common.sh

################################################################################

function installWebServer()
{
    readBold "Do you want to install WEB SERVER? y or n"
    if [[ $REPLY =~ ^[Yy]$ ]]
    then
        printGreen "Installing WEB SERVER ..."

        readBold "Do you want to install APACHE2? y or n"
        if [[ $REPLY =~ ^[Yy]$ ]]
        then
            printGreen "Installing APACHE2 ..."

            sudo apt install -y \
                apache2
        fi

        readBold "Do you want to install NGINX? y or n"
        if [[ $REPLY =~ ^[Yy]$ ]]
        then
            printGreen "Installing NGINX ..."

            sudo apt install -y \
                nginx
        fi

        readBold "Do you want to install MYSQL? y or n"
        if [[ $REPLY =~ ^[Yy]$ ]]
        then
            printGreen "Installing MYSQL ..."

            sudo apt install -y \
                mysql-client \
                mysql-server
        fi

        readBold "Do you want to install MARIADB? y or n"
        if [[ $REPLY =~ ^[Yy]$ ]]
        then
            printGreen "Installing MARIADB ..."

            sudo apt install -y \
                mariadb-client \
                mariadb-server
        fi

        readBold "Do you want to install PHP? y or n"
        if [[ $REPLY =~ ^[Yy]$ ]]
        then
            printGreen "Installing PHP ..."

            sudo apt install -y \
                php \
                php-intl
        fi

        readBold "Do you want to install PHPMYADMIN? y or n"
        if [[ $REPLY =~ ^[Yy]$ ]]
        then
            printGreen "Installing PHPMYADMIN ..."

            sudo apt install -y \
                phpmyadmin
        fi
    fi
}

installWebServer
