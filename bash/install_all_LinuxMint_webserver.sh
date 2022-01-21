#!/bin/bash

################################################################################

function installWebServer()
{
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
}
