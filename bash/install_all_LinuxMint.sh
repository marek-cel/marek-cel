#!/bin/bash

################################################################################

source install_all_LinuxMint_common.sh
source install_all_LinuxMint_essentials.sh
source install_all_LinuxMint_aitools.sh
source install_all_LinuxMint_celestia.sh
source install_all_LinuxMint_creativetools.sh
source install_all_LinuxMint_extras.sh
source install_all_LinuxMint_dev.sh
source install_all_LinuxMint_webserver.sh
source install_all_LinuxMint_docker.sh
source install_all_LinuxMint_cax.sh
source install_all_LinuxMint_vnc.sh
source install_all_LinuxMint_flightgear.sh
source install_all_LinuxMint_kodi.sh

################################################################################

installEssentials
installAiTools
installCelestia
installCreativeTools
installExtras
installDevelopEssentials
installWebServer
installDcoker
installCaxGisScientific
installVnc
installFlightGear
installKodi

################################################################################

notify-send "Installation finished."
printGreen "Installation finished."
read -p "Press any key to continue... " -n1 -s
echo
