#!/bin/bash

################################################################################

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

rm -f coverage_full.info
rm -f coverage.info
rm -r -f coverage-report
cd bin; ./exec; cd ..;
$LCOV_TOOL --capture \
    --gcov-tool $GCOV_TOOL \
    --base-directory . \
    --no-external \
    --directory $BASE_DIR \
    --output-file coverage.info
$GENHTML_TOOL coverage.info \
    --legend \
    --function-coverage \
    --output-directory coverage-report

################################################################################
