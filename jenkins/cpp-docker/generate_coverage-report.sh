#!/bin/bash

################################################################################

rm -f coverage.info
rm -r -f coverage-report

lcov --capture \
    --base-directory ./src \
    --no-external \
    --directory ./build \
    --output-file coverage.info

genhtml coverage.info \
    --legend \
    --function-coverage \
    --output-directory coverage-report

################################################################################
