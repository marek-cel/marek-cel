#!/bin/bash

rm -r -f bin
rm -r -f build

mkdir build
cd build

cmake .. \
	-DCMAKE_BUILD_TYPE=Release \
	-DCMAKE_INSTALL_PREFIX=/usr/local \
	-DCMAKE_CXX_FLAGS="-O0 -fno-elide-constructors -fno-default-inline -fprofile-arcs -ftest-coverage"

make -j4
