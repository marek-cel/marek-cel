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

# https://docs.docker.com/get-docker/
function installDcoker()
{
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
}

################################################################################

sudo apt install -y \
    apache2 \
    git \
    mc \
    mysql-client \
    mysql-server \
    net-tools \
    php \
    phpmyadmin \
    rsync \
    samba \
    tree \
    vsftpd \
    whois

################################################################################

installDcoker

################################################################################

read -p "Press any key to continue... " -n1 -s
