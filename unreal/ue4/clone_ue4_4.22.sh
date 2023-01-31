#!/bin/bash

rm -rf temp

# git clone --single-branch --branch 4.22 https://github.com/EpicGames/UnrealEngine.git temp
git clone --single-branch --branch 4.22 git@github.com:EpicGames/UnrealEngine.git temp


read -p "Press any key to continue... " -n1 -s
