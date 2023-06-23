#!/bin/bash

# mylist.txt:
# file '01.wmv'
# file '02.wmv'
# file '03.wmv'

OUTPUT="output.wmv"

ffmpeg -f concat -i mylist.txt -c copy $OUTPUT

notify-send "Video processing finished."
read -p "Press any key to continue... " -n1 -s
