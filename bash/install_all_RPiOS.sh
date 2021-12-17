#!/bin/bash

################################################################################
# ESSENTIALS
################################################################################

# sudo apt update

sudo mysql_secure_installation

sudo apt install -y \
    apache2 \
    ffmpeg \
    imagemagick \
    mc \
    mplayer \
    ntfs-3g \
    openssh-server \
    php \
    phpmyadmin \
    psensor \
    rsync \
    samba \
    samba-common-bin \
    vsftpd \
    whois

# TODO: mysql phpmyadmin

################################################################################
# UPGRADE
################################################################################

sudo apt full-upgrade
# sudo apt upgrade

################################################################################

read -p "Press any key to continue... " -n1 -s
