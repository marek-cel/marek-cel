#!/bin/bash

################################################################################

source install_common.sh

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
            bridge-utils \
            guestfs-tools \
            libvirt-clients \
            libvirt-daemon-system \
            ovmf \
            qemu-kvm \
            qemu-system-x86 \
            qemu-utils \
            virt-manager \
            virt-viewer \
            virtinst
            

        sudo systemctl enable --now libvirtd
        sudo systemctl start libvirtd
        sudo systemctl status libvirtd

        sudo usermod -aG kvm $USER
        sudo usermod -aG libvirt $USER

    fi
}

installKVM
