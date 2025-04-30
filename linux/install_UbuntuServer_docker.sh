#!/usr/bin/env bash

################################################################################

source install_common.sh

################################################################################

# https://docs.docker.com/get-docker/
function installDcoker()
{
    readBold "Do you want to install DOCKER?"
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
        printYellow "Log out and log in again."
    fi
}

installDcoker
