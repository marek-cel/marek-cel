#!/bin/bash

rm -rf UnrealEngine-4.24

# git clone --single-branch --branch 4.24 https://github.com/EpicGames/UnrealEngine.git temp
git clone --single-branch --branch 4.24 git@github.com:EpicGames/UnrealEngine.git temp


read -p "Press any key to continue... " -n1 -s
