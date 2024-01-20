#!/bin/bash

################################################################################

BUILD_DIR="${1%/}"

LCOV_TOOL=lcov
GENHTML_TOOL=genhtml
GCOV_TOOL=gcov

# LCOV_TOOL=/usr/local/bin/lcov
# GENHTML_TOOL=/usr/local/bin/genhtml
# GCOV_TOOL=gcov

# LCOV_TOOL=lcov
# GENHTML_TOOL=genhtml
# GCOV_TOOL=llvm-gcov.sh

BASE_DIR=./src

################################################################################

if [ ! -z "$BUILD_DIR" ]
then
    rm -f coverage_full.info
    rm -f coverage.info
    rm -r -f coverage-report
    cd bin; ./tests; cd ..;
    mapfile -t exclude < lcov_exclude.txt
    $LCOV_TOOL --capture \
        --gcov-tool $GCOV_TOOL \
        --base-directory $BASE_DIR \
        --no-external \
        --directory $BUILD_DIR \
        --output-file coverage_full.info
    $LCOV_TOOL --remove coverage_full.info \
        ${exclude[@]} \
        -o coverage.info
    $GENHTML_TOOL coverage.info \
        --legend \
        --function-coverage \
        --output-directory coverage-report
else
    echo
    echo Error! Build directory path not specified.
    echo Usage:
    echo ./generate_coverage-report.sh BUILD_DIRECTORY_PATH
    echo
    read -p "Press any key to continue... " -n1 -s
    echo
fi

################################################################################
