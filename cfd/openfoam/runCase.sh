#!/bin/bash

################################################################################

CURRENT_DIR=$(pwd)

rm -r $FOAM_RUN/$1
cp -r $1 $FOAM_RUN/
cd $FOAM_RUN/$1
./Allrun
cd $CURRENT_DIR
