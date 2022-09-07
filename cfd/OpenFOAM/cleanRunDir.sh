#!/bin/bash

################################################################################

CURRENT_DIR=$(pwd)

CASE_DIR=$(basename $1)

cd $FOAM_RUN
rm -rf *
