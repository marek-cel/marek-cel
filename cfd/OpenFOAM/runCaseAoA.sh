#!/bin/bash

################################################################################

if [ -d "$1" ]; then
    CASE_DIR=${1%/}
    AOA=0
    
    # start value from command line
    if [ -n "$2" ]; then
        AOA=$2
    fi
    
    rm -r "$FOAM_RUN/$CASE_DIR"_"$AOA"
    cp -r $CASE_DIR "$FOAM_RUN/$CASE_DIR"_"$AOA"
    mv "$FOAM_RUN/$CASE_DIR"_"$AOA"/constant/triSurface/model.stl "$FOAM_RUN/$CASE_DIR"_"$AOA"/constant/triSurface/model_bak.stl
    surfaceTransformPoints -rotate-y $AOA "$FOAM_RUN/$CASE_DIR"_"$AOA"/constant/triSurface/model_bak.stl "$FOAM_RUN/$CASE_DIR"_"$AOA"/constant/triSurface/model.stl
    rm "$FOAM_RUN/$CASE_DIR"_"$AOA"/constant/triSurface/model_bak.stl
    cd "$FOAM_RUN/$CASE_DIR"_"$AOA"
    ./Allrun
    EXIT_CODE=$?
    if [ $EXIT_CODE -ne 0 ]; then exit $EXIT_CODE; fi
    cd ..
    COEFFS_FILE="$FOAM_RUN"/coeffs_"$CASE_DIR".dat
    if ! [ -f "$COEFFS_FILE" ]; then
        head -n 13 "$FOAM_RUN/$CASE_DIR"_"$AOA"/postProcessing/forceCoeffs/0/coefficient.dat &>> $COEFFS_FILE
        echo "" &>> $COEFFS_FILE
    fi
    printf "%d\t" $AOA &>> $COEFFS_FILE
    tail -n 1 "$FOAM_RUN/$CASE_DIR"_"$AOA"/postProcessing/forceCoeffs/0/coefficient.dat &>> $COEFFS_FILE
else
    echo "Please provide valid case directory"
fi

################################################################################
