#!/bin/bash

rm -r -f UnrealEngine-4.22
cp -r temp UnrealEngine-4.22
cd UnrealEngine-4.22

./Setup.sh
if [ $? -eq 0 ]; then
  ./GenerateProjectFiles.sh
  if [ $? -eq 0 ]; then
    make # DO NOT USE -j 4!!!
  fi
fi

read -p "Press any key to continue... " -n1 -s
