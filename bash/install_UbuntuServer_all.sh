#!/bin/bash

################################################################################

source install_common.sh

source install_UbuntuServer_essentials.sh
source install_UbuntuServer_develop.sh
source install_UbuntuServer_docker.sh
source install_UbuntuServer_file_server.sh
source install_UbuntuServer_gitlab.sh
source install_UbuntuServer_jenkins.sh
source install_UbuntuServer_kvm.sh
source install_UbuntuServer_web_server.sh
source install_UbuntuServer_zone_minder.sh

################################################################################

printGreen "Installation finished."
read -p "Press any key to continue... " -n1 -s
echo
