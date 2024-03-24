#!/bin/bash

rm -r build-*

# Get a list of all directories in the current working directory
DIRS=($(ls -d */))

# Iterate through the array and clean
for DIR in "${DIRS[@]}"; do
    cd $DIR
    rm -r bin
    rm -r build
    rm -r .vscode
    cd ..
done

read -p "Press Enter to exit..."
