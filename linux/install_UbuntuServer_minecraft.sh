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
            openjdk-21-jre-headless \
            screen

        wget https://piston-data.mojang.com/v1/objects/e6ec2f64e6080b9b5d9b471b291c33cc7f509733/server.jar
        mv server.jar $HOME/minecraft_server_1.21.5.jar

        currentDir=$(pwd)
        cd $HOME

        printYellow "Opening port 25565 for MINECRAFT SERVER ..."
        sudo ufw allow 25565

        printYellow "Starting MINECRAFT SERVER ..."
        java -Xms1024M -Xmx1024M -jar minecraft_server_1.21.5.jar nogui

        vi eula.txt

        cd $currentDir
    fi
}

installMinecraftServer
