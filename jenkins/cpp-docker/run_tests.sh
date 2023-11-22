#!/bin/bash

export LD_LIBRARY_PATH=$LD_LIBRARY_PATH:/usr/local/lib

cd bin
./tests --gtest_filter=*
