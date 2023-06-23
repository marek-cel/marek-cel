#!/bin/bash

################################################################################

source install_all_WSL2_common.sh
source install_all_WSL2_essentials.sh
source install_all_WSL2_develop.sh
source install_all_WSL2_cax.sh

################################################################################

installEssentials
installDevelopEssentials
installCaxGisScientific

################################################################################

read -p "Press any key to continue... " -n1 -s
