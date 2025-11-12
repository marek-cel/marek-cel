#!/usr/bin/env bash

################################################################################

source install_common.sh

################################################################################

function installMinecraftServer()
{
    readBold "Do you want to install MINECRAFT SERVER?"
    if [[ $REPLY =~ ^[Yy]$ ]]
    then
        printGreen "Installing MINECRAFT SERVER ..."

        sudo apt install -y \
            nmap \
            openjdk-21-jdk \
            openjdk-21-jre-headless \
            screen \
            wget

        printYellow "Opening port 25565 for MINECRAFT SERVER ..."
        sudo ufw allow 25565

        sudo useradd -m -r -d /opt/minecraft minecraft

        currentDir=$(pwd)
        cd /opt/minecraft

        wget https://piston-data.mojang.com/v1/objects/6bce4ef400e4efaa63a13d5e6f6b500be969ef81/server.jar
        sudo mv server.jar minecraft_server_1.21.8.jar


        printYellow "Starting MINECRAFT SERVER ..."
        sudo su - minecraft -c "java -Xms1024M -Xmx1024M -jar minecraft_server_1.21.8.jar nogui"

        sudo su - minecraft -c "vi eula.txt"

        cd $currentDir
    fi
}

installMinecraftServer
