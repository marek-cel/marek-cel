#!/bin/bash

################################################################################

sudo apt install -y \
    autoconf \
    automake \
    build-essential \
    cmake \
    linux-tools-common \
    mc \
    rsync \
    tree \
    whois

sudo apt install -y \
    openssh-server

################################################################################

read -p "Press any key to continue... " -n1 -s
