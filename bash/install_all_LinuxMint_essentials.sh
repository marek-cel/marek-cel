#!/bin/bash

################################################################################

function installEssentials()
{
    readBold "Do you want to install ESSENTIALS? y or n"
    if [[ $REPLY =~ ^[Yy]$ ]]
    then
        printGreen "Installing ESSENTIALS ..."

        sudo apt install -y \
            chromium \
            djvulibre-bin \
            dropbox \
            ffmpeg \
            gparted \
            imagemagick \
            joystick \
            kate \
            konsole \
            language-selector-common \
            linux-tools-common \
            mc \
            mplayer \
            okular \
            openssh-server \
            psensor \
            rsync \
            samba \
            smartmontools \
            smplayer \
            traceroute \
            tree \
            ttf-mscorefonts-installer \
            vlc \
            vsftpd \
            webp \
            whois

        # BRAVE BROWSER
        readBold "Do you want to install BRAVE BROWSER? y or n"
        if [[ $REPLY =~ ^[Yy]$ ]]
        then
            printGreen "Installing BRAVE BROWSER ..."
            
            sudo apt install \
                apt-transport-https \
                curl
                
            sudo curl -fsSLo /usr/share/keyrings/brave-browser-archive-keyring.gpg \
                https://brave-browser-apt-release.s3.brave.com/brave-browser-archive-keyring.gpg

            echo "deb [signed-by=/usr/share/keyrings/brave-browser-archive-keyring.gpg arch=amd64] https://brave-browser-apt-release.s3.brave.com/ stable main"| \
                sudo tee /etc/apt/sources.list.d/brave-browser-release.list

            sudo apt update
            sudo apt install brave-browser
        fi
        
        # SNAP STORE
        readBold "Do you want to install SNAP STORE? y or n"
        if [[ $REPLY =~ ^[Yy]$ ]]
        then
            printGreen "Installing SNAP STORE ..."
            
            sudo rm /etc/apt/preferences.d/nosnap.pref
            sudo apt update
            sudo apt install snapd snap-store 
        fi
    fi
}
