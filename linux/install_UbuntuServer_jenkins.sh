#!/usr/bin/env bash

################################################################################

source install_common.sh

################################################################################

# https://www.jenkins.io/doc/book/installing/linux/
function installJenkins()
{
    readBold "Do you want to install JENKINS? y or n"
    if [[ $REPLY =~ ^[Yy]$ ]]
    then
        printGreen "Installing JENKINS ..."

        sudo apt update

        sudo apt install -y \
            fontconfig \
            openjdk-17-jdk \
            openjdk-17-jre

        java -version

        sudo wget -O /usr/share/keyrings/jenkins-keyring.asc https://pkg.jenkins.io/debian-stable/jenkins.io-2023.key

        echo deb [signed-by=/usr/share/keyrings/jenkins-keyring.asc] \
            https://pkg.jenkins.io/debian-stable binary/ | sudo tee \
            /etc/apt/sources.list.d/jenkins.list > /dev/null

        sudo apt-get update
        sudo apt-get install -y \
            jenkins

        sudo usermod -aG docker jenkins
    fi
}

installJenkins
