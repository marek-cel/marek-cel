#!/bin/bash

################################################################################

build_dir="${1%/}"

cp $build_dir/tests/*.gcda ./src
cp $build_dir/tests/*.gcno ./src

cd src
for file in ./*.cpp
do
  gcov -b -f "$file"
done

################################################################################
