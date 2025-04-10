#!/usr/bin/env bash

################################################################################

source install_common.sh

source install_RPiOS_essentials.sh
source install_RPiOS_develop.sh

################################################################################

printGreen "Installation finished."
read -p "Press any key to continue... " -n1 -s
echo
