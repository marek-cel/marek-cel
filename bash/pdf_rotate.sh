#!/bin/bash

################################################################################
# To use ImageMagick, edit /etc/ImageMagick-6/policy.xml and set
# <policy domain="coder" rights="read|write" pattern="PDF" />
################################################################################

INPUT="input.pdf"
OUTPUT="output.pdf"

qpdf $INPUT $OUTPUT --rotate=+90:1-z
