#!/bin/bash

INPUT="input.mp4"
OUTPUT="output.mp4"

# start time
S_H=0
S_M=0
S_S=55

# end time
E_H=0
E_M=1
E_S=5

# time calculations
T_S=$(expr 3600 \* $S_H + 60 \* $S_M + $S_S )
T_E=$(expr 3600 \* $E_H + 60 \* $E_M + $E_S )

# duration
T_L=$(expr $T_E - $T_S )
L_H=$(expr $T_L / 3600 )
L_M=$(expr $(expr $T_L - 3600 \* $L_H ) / 60 )
L_S=$(expr $T_L - 3600 \* $L_H - 60 \* $L_M )

START=`printf %02d ${S_H}`:`printf %02d ${S_M}`:`printf %02d ${S_S}`
DURAT=`printf %02d ${L_H}`:`printf %02d ${L_M}`:`printf %02d ${L_S}`

# avconv -i $INPUT -ss $START -t $DURAT -codec copy -threads 4 $OUTPUT
ffmpeg -i $INPUT -ss $START -t $DURAT -codec copy -threads 4 $OUTPUT

notify-send "Video processing finished."
read -p "Press any key to continue... " -n1 -s
