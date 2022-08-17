#!/bin/bash

################################################################################

CURRENT_DIR=$(pwd)

CASE_DIR=$(basename $1)

rm -r $FOAM_RUN/$CASE_DIR
cp -r $1 $FOAM_RUN/
cd $FOAM_RUN/$CASE_DIR
./Allrun
cd $CURRENT_DIR
