#!/bin/bash

rm -r -f temp
cp -r UnrealEngine-4.22 temp
cd temp

./Setup.sh

if [ $? -eq 0 ]; then
  ./GenerateProjectFiles.sh
  if [ $? -eq 0 ]; then
    make -j 4
  fi
fi

read -p "Press any key to continue... " -n1 -s
