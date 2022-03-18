#!/bin/bash

################################################################################

rm -f out_cpplint.txt

cpplint.py \
    --filter=-build/c++11,+build/c++14,-readability/multiline_comment,-readability/alt_tokens,-whitespace/parens,-whitespace/braces,-whitespace/indent,-whitespace/comments,-whitespace/newline,-whitespace/blank_line \
    --linelength=100 \
    --extensions=h,cpp --root=./include \
    ./include/*.h \
    ./src/*.cpp \
    2> out_cpplint.txt

################################################################################
