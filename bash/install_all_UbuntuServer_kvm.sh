#!/bin/bash

################################################################################

function installKVM()
{
    readBold "Do you want to install QEMU/KVM? y or n"
    if [[ $REPLY =~ ^[Yy]$ ]]
    then
        printGreen "Installing QEMU/KVM ..."

        sudo apt install -y \
            cpu-checker
        
        sudo apt install -y \
            qemu-kvm \
            virt-manager \
            libvirt-daemon-system \
            virtinst \
            libvirt-clients \
            bridge-utils

        sudo systemctl enable --now libvirtd
        sudo systemctl start libvirtd
        sudo systemctl status libvirtd

        sudo usermod -aG kvm $USER
        sudo usermod -aG libvirt $USER

    fi
}
