#!/usr/bin/env bash

################################################################################

source install_common.sh

################################################################################

function installExtras()
{
    readBold "Do you want to install ENTERTEINMENT?"
    if [[ $REPLY =~ ^[Yy]$ ]]
    then
        printGreen "Installing ENTERTEINMENT ..."

        sudo apt install -y \
            cmatrix \
            cmatrix-xfont \
            handbrake \
            hollywood \
            qmmp \
            spotify-client
    fi

    readBold "Do you want to install EMULATORS?"
    if [[ $REPLY =~ ^[Yy]$ ]]
    then
        printGreen "Installing EMULATORS ..."

        sudo apt install -y \
            dosbox \
            retroarch \
            wine
    fi

    readBold "Do you want to install REMOTE DESKTOP CLIENTS?"
    if [[ $REPLY =~ ^[Yy]$ ]]
    then
        printGreen "Installing REMOTE DESKTOP CLIENTS ..."

        sudo apt install -y \
            remmina \
            remmina-plugin-rdp \
            remmina-plugin-vnc
    fi

    readBold "Do you want to install VIRTUAL BOX?"
    if [[ $REPLY =~ ^[Yy]$ ]]
    then
        printGreen "Installing VIRTUAL BOX ..."

        sudo apt install -y \
            virtualbox \
            virtualbox-ext-pack \
            virtualbox-guest-additions-iso \
            virtualbox-qt
    fi

    readBold "Do you want to install QEMU/KVM?"
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

installExtras