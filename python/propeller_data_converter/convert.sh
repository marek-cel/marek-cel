#!/bin/bash

################################################################################

function run()
{
    ./convert.py csv/input/"$1"_qc.csv csv/input/"$1"_tc.csv csv/output/"$1"_cp.csv csv/output/"$1"_ct.csv
}

################################################################################

rm csv/output/*

run "5868-9_2"
run "5868-9_3"
run "5868-9_4"
run "5868-r6_2"
run "5868-r6_3"
run "5868-r6_4"
