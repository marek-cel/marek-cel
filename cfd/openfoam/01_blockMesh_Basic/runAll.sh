#!/bin/bash
cd ${0%/*} || exit 1    # Run from this directory

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

# Source run functions
. $WM_PROJECT_DIR/bin/tools/RunFunctions

################################################################################

TIME_0=$(date +%s)
echo $(date +%Y-%m-%d\ %H:%M:%S) - Computations started

################################################################################
# EXECUTION - START
################################################################################

echo "Running blockMesh"
TMP_0=$(date +%s)
blockMesh > log.blockMesh 2>&1
EXIT_CODE=$?
printExecutionTime "blockMesh finished in " $TMP_0 "with exit code" $EXIT_CODE
if [ $EXIT_CODE -ne 0 ]; then exit 1; fi

echo "Running checkMesh"
TMP_0=$(date +%s)
checkMesh > log.checkMesh 2>&1
EXIT_CODE=$?
printExecutionTime "checkMesh finished in " $TMP_0 "with exit code" $EXIT_CODE
if [ $EXIT_CODE -ne 0 ]; then exit 1; fi

################################################################################
# EXECUTION - FINISH
################################################################################

printExecutionTime "OpenFOAM finished in " $TIME_0
