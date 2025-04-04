#!/bin/bash

################################################################################

source install_common.sh

################################################################################

function installWebServer()
{
    readBold "Do you want to install WEB SERVER?"
    if [[ $REPLY =~ ^[Yy]$ ]]
    then
        printGreen "Installing WEB SERVER ..."

        readBold "Do you want to install APACHE2?"
        if [[ $REPLY =~ ^[Yy]$ ]]
        then
            printGreen "Installing APACHE2 ..."

            sudo apt install -y \
                apache2
        fi

        readBold "Do you want to install NGINX?"
        if [[ $REPLY =~ ^[Yy]$ ]]
        then
            printGreen "Installing NGINX ..."

            sudo apt install -y \
                nginx
        fi

        readBold "Do you want to install MYSQL?"
        if [[ $REPLY =~ ^[Yy]$ ]]
        then
            printGreen "Installing MYSQL ..."

            sudo apt install -y \
                mysql-client \
                mysql-server
        fi

        readBold "Do you want to install MARIADB?"
        if [[ $REPLY =~ ^[Yy]$ ]]
        then
            printGreen "Installing MARIADB ..."

            sudo apt install -y \
                mariadb-client \
                mariadb-server
        fi

        readBold "Do you want to install PHP?"
        if [[ $REPLY =~ ^[Yy]$ ]]
        then
            printGreen "Installing PHP ..."

            sudo apt install -y \
                php \
                php-intl
        fi

        readBold "Do you want to install POSTGRESQL?"
        if [[ $REPLY =~ ^[Yy]$ ]]
        then
            printGreen "Installing POSTGRESQL ..."

            sudo apt install -y \
                postgresql \
                postgresql-contrib
        fi

        readBold "Do you want to install PHPMYADMIN?"
        if [[ $REPLY =~ ^[Yy]$ ]]
        then
            printGreen "Installing PHPMYADMIN ..."

            sudo apt install -y \
                phpmyadmin
        fi

        readBold "Do you want to install PHPPGADMIN?"
        if [[ $REPLY =~ ^[Yy]$ ]]
        then
            printGreen "Installing PHPPGADMIN ..."

            sudo apt install -y \
                phppgadmin
        fi
    fi
}

installWebServer