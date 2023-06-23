#!/bin/bash

# sudo apt install webp

FILES=$(ls | grep webp)

mkdir out

for f in $FILES
do
 echo "Processing $f"
 dwebp $f -o out/$f.png
done
