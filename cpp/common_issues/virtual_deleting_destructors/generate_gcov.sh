#!/bin/bash

################################################################################

./generate_coverage-report.sh
gcov -b -f src/main.cpp
gcov -b -f src/BaseClass.cpp
gcov -b -f src/DerivedClass.cpp
mv *.gcov ./src

################################################################################
