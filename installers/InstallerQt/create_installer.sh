#!/bin/bash

################################################################################

INSTALLER_NAME=testapp-1.0

rm $INSTALLER_NAME
rm qti/$INSTALLER_NAME

TESTAPP_DIR=qti/packages/pl.marekcel.testapp

cp bin/test $TESTAPP_DIR/data

cp LICENSE.txt $TESTAPP_DIR/meta

cd qti

$HOME/bin/Qt/QtIFW-3.2.0/bin/binarycreator -c config/config.xml -p packages $INSTALLER_NAME

mv $INSTALLER_NAME ../$INSTALLER_NAME

################################################################################

read -p "Press any key to continue..." -n1 -s
