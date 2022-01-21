#!/bin/bash

################################################################################

rm -f log_cppcheck.txt

cppcheck --enable=style --std=c++17 -I ./include ./src 2> log_cppcheck.txt

################################################################################

read -p "Press any key to continue... " -n1 -s

