#!/bin/bash

lsblk

echo "Image will be installed on /dev/mmcblk0"
read -p "Press any key to continue... " -n1 -s
echo

sudo dd bs=4M if=OSMC_TGT_rbp2_20190522.img of=/dev/mmcblk0

notify-send "Installation finished."
echo "Installation finished."
read -p "Press any key to continue... " -n1 -s
echo
