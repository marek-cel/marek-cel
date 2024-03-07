#!/bin/bash

################################################################################

source install_common.sh

################################################################################

function installEssentials()
{
    readBold "Do you want to install ESSENTIALS? y or n"
    if [[ $REPLY =~ ^[Yy]$ ]]
    then
        printGreen "Installing ESSENTIALS ..."

        sudo apt install -y \
            breeze \
            chromium \
            djvulibre-bin \
            dropbox \
            ffmpeg \
            glmark2 \
            gparted \
            imagemagick \
            joystick \
            jstest-gtk \
            kate \
            konsole \
            language-selector-common \
            linux-tools-common \
            mc \
            mesa-utils \
            mplayer \
            nfs-common \
            okular \
            openssh-server \
            plasma-desktop \
            psensor \
            rsync \
            samba \
            smartmontools \
            smplayer \
            systemsettings \
            torbrowser-launcher \
            traceroute \
            tree \
            ttf-mscorefonts-installer \
            vim \
            vlc \
            vsftpd \
            webp \
            whois \
            xboxdrv
        
        sudo flatpak install flathub md.obsidian.Obsidian

        # BRAVE BROWSER
        readBold "Do you want to install BRAVE BROWSER? y or n"
        if [[ $REPLY =~ ^[Yy]$ ]]
        then
            printGreen "Installing BRAVE BROWSER ..."
            
            sudo apt install -y \
                apt-transport-https \
                curl
                
            sudo curl -fsSLo /usr/share/keyrings/brave-browser-archive-keyring.gpg \
                https://brave-browser-apt-release.s3.brave.com/brave-browser-archive-keyring.gpg

            echo "deb [signed-by=/usr/share/keyrings/brave-browser-archive-keyring.gpg arch=amd64] https://brave-browser-apt-release.s3.brave.com/ stable main"| \
                sudo tee /etc/apt/sources.list.d/brave-browser-release.list

            sudo apt update
            sudo apt install -y brave-browser
        fi
    fi
}

installEssentials