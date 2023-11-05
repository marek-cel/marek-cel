#!/bin/bash

################################################################################

source install_all_UbuntuServer_common.sh
source install_all_UbuntuServer_docker.sh
source install_all_UbuntuServer_file_server.sh
source install_all_UbuntuServer_kvm.sh
source install_all_UbuntuServer_web_server.sh
source install_all_UbuntuServer_zone_minder.sh

################################################################################

sudo apt install -y \
    bridge-utils \
    mc \
    net-tools \
    network-manager \
    rsync \
    tree \
    whois

################################################################################

installDcoker
installFileServer
installKVM
installWebServer
installZoneMinder

################################################################################

read -p "Press any key to continue... " -n1 -s
