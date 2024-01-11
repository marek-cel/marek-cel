#!/bin/bash

function printExecutionTime()
{
    TIME_1=$(date +%s)
    TIME_T=$(expr $TIME_1 - $2 )
    TIME_H=$(expr $TIME_T / 3600 )
    TIME_M=$(expr $(expr $TIME_T - 3600 \* $TIME_H ) / 60 )
    TIME_S=$(expr $TIME_T - 3600 \* $TIME_H - 60 \* $TIME_M )
    TIME_F=`printf %02d ${TIME_H}`:`printf %02d ${TIME_M}`:`printf %02d ${TIME_S}`
    echo "$1 $TIME_F $3 $4"
}

if [ -n "$1" ]; then
    if [ "$1" == "-help" ]; then
        echo "./runCaseSequance.sh <path to case directory> <AoA start value> <AoA end value> <AoA step>"
        exit 0
    fi
fi

if [ -d "$1" ]; then
    CASE_DIR=$(basename $1)
    
    # default iteration values
    START=0
    END=$START
    STEP=1

    # start value from command line
    if [ -n "$2" ]; then
        START=$2
    fi

    # end value from command line
    if [ -n "$3" ]; then
        if [ $3 -gt $START ]; then
            END=$3
        fi
    fi

    # step value from command line
    if [ -n "$4" ]; then
        if [ $4 -gt 0 ]; then
            STEP=$4
        fi
    fi
    
    TIME_0=$(date +%s)
    echo $(date +%Y-%m-%d\ %H:%M:%S) - Computations started

    for (( AOA=$START; AOA<=$END; AOA+=$STEP ))
    do
        ./runCaseAoA.sh $1 $AOA
        EXIT_CODE=$?
        if [ $EXIT_CODE -ne 0 ]; then exit $EXIT_CODE; fi
    done
    
    printExecutionTime "OpenFOAM sequence finished in " $TIME_0
else
    echo "Please provide valid case directory"
fi
