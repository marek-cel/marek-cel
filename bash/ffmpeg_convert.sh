#!/bin/bash

INPUT="input.avi"
OUTPUT="output.mp4"

ffmpeg -i $INPUT -acodec copy -vcodec mpeg4 -threads 4 $OUTPUT
# ffmpeg -i $INPUT -acodec aac -vcodec mpeg4 -threads 4 $OUTPUT
# ffmpeg -i $INPUT -acodec copy -vcodec libx264 -threads 4 $OUTPUT

# OUTPUT="output.wmv"
# ffmpeg -i $INPUT -b:v 1024k -acodec wmav2 -vcodec wmv2 -threads 4 $OUTPUT

notify-send "Video processing finished."
read -p "Press any key to continue... " -n1 -s
