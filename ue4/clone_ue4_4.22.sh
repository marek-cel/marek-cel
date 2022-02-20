#!/bin/bash

rm -rf UnrealEngine-4.22

# git clone --single-branch --branch 4.22 https://github.com/EpicGames/UnrealEngine.git UnrealEngine-4.22
git clone --single-branch --branch 4.22 git@github.com:EpicGames/UnrealEngine.git UnrealEngine-4.22


read -p "Press any key to continue... " -n1 -s
