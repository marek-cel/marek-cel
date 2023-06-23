#!/bin/bash

################################################################################
# To use ImageMagick, edit /etc/ImageMagick-6/policy.xml and set
# <policy domain="coder" rights="read|write" pattern="PDF" />
################################################################################

INPUT="input.pdf"
OUTPUT="output.pdf"

# preserves document meta data
# qpdf $INPUT --pages . 461-495 -- $OUTPUT

# DOES NOT preserve document meta data
qpdf --empty --pages $INPUT 461-495 -- $OUTPUT
