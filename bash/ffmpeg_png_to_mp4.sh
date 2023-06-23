#!/bin/bash

ffmpeg -framerate 10 -pattern_type glob -i '*.png' -c:v libx264 -pix_fmt yuv420p 000_out.mp4

notify-send "Video processing finished."
read -p "Press any key to continue... " -n1 -s
