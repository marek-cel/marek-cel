#!/bin/bash

################################################################################

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

################################################################################

function runCaseForAngleOfAttack()
{
    EXEC_DIR=$(pwd)

    rm -r "$FOAM_RUN/$1"_"$2"
    cp -r $1 "$FOAM_RUN/$1"_"$2"
    mv "$FOAM_RUN/$1"_"$2"/constant/triSurface/model.stl "$FOAM_RUN/$1"_"$2"/constant/triSurface/model_bak.stl
    surfaceTransformPoints -rotate-y $2 "$FOAM_RUN/$1"_"$2"/constant/triSurface/model_bak.stl "$FOAM_RUN/$1"_"$2"/constant/triSurface/model.stl
    rm "$FOAM_RUN/$1"_"$2"/constant/triSurface/model_bak.stl
    cd "$FOAM_RUN/$1"_"$2"
    ./Allrun
    EXIT_CODE=$?
    if [ $EXIT_CODE -ne 0 ]; then exit $EXIT_CODE; fi
    cd ..
    if [ $3 -eq 1 ]; then
        head -n 13 "$FOAM_RUN/$1"_"$2"/postProcessing/forceCoeffs/0/coefficient.dat &>> "$FOAM_RUN"/coefficient_"$1".dat
        echo "" &>> "$FOAM_RUN"/coefficient_"$1".dat
    fi
    printf "%d\t" $2 &>> "$FOAM_RUN"/coefficient_"$1".dat
    tail -n 1 "$FOAM_RUN/$1"_"$2"/postProcessing/forceCoeffs/0/coefficient.dat &>> "$FOAM_RUN"/coefficient_"$1".dat
    cd $EXEC_DIR
}

################################################################################

if [ -n "$1" ]; then
    if [ "$1" == "-help" ]; then
        echo "./runCaseSequance.sh <path to case directory> <AoA start value> <AoA end value> <AoA step>"
        exit 0
    fi
fi

if [ -d "$1" ]; then
    CASE_DIR=${1%/}
    
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
    
    rm "$FOAM_RUN"/coefficient_"$CASE_DIR".dat

    ITERATION=1

    for (( AOA=$START; AOA<=$END; AOA+=$STEP ))
    do
        runCaseForAngleOfAttack $CASE_DIR $AOA $ITERATION
        ((ITERATION+=1))
    done
    
    printExecutionTime "OpenFOAM sequence finished in " $TIME_0
else
    echo "Please provide valid case directory"
fi



################################################################################
