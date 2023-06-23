#!/bin/bash

# avconv -f x11grab -r 25 -s 1920x1080 -i :0.0 -vcodec libx264 -pre lossless_ultrafast -threads 0 $HOME/output.mp4
ffmpeg -f x11grab -framerate 25 -s 1920x1080 -i :0.0 -vcodec libx264 -preset ultrafast -threads 0 $HOME/output.mp4
