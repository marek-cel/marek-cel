#!/usr/bin/env bash

################################################################################

source install_common.sh

source install_LinuxMint_essentials.sh
source install_LinuxMint_aitools.sh
source install_LinuxMint_celestia.sh
source install_LinuxMint_creative.sh
source install_LinuxMint_extras.sh
source install_LinuxMint_develop.sh
source install_LinuxMint_webserver.sh
source install_LinuxMint_docker.sh
source install_LinuxMint_cax.sh
source install_LinuxMint_vnc.sh
source install_LinuxMint_flightgear.sh
source install_LinuxMint_kodi.sh

################################################################################

notify-send "Installation finished."
printGreen "Installation finished."
read -p "Press any key to continue... " -n1 -s
echo
