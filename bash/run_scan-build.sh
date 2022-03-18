#!/bin/bash

################################################################################

rm -r -f build
mkdir build
cd build

cmake .. \
    -DCMAKE_BUILD_TYPE=Release
    
scan-build-10 \
    -analyze-headers \
    make -j 4

################################################################################
