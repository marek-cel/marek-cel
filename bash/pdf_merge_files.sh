#!/bin/bash

################################################################################
# To use ImageMagick, edit /etc/ImageMagick-6/policy.xml and set
# <policy domain="coder" rights="read|write" pattern="PDF" />
################################################################################

OUTPUT="output.pdf"

FILES=$(ls | grep pdf)

# convert $FILES $OUTPUT
# convert -density 30x150 -quality 100 $FILES $OUTPUT

# gs -dBATCH -dCompatibilityLevel=1.4 -dPDFSETTINGS=/default -dNOPAUSE -q -sDEVICE=pdfwrite -sOutputFile=$OUTPUT *.pdf
# gs -dBATCH -dCompatibilityLevel=1.4 -dPDFSETTINGS=/prepress -dNOPAUSE -q -sDEVICE=pdfwrite -sOutputFile=$OUTPUT *.pdf

# gs -dBATCH -dCompatibilityLevel=1.4 -dPDFSETTINGS=/screen -dNOPAUSE -q -sDEVICE=pdfwrite -dDetectDuplicateImages -dCompressFonts=true -r150 -sOutputFile=$OUTPUT *.pdf
# gs -dBATCH -dCompatibilityLevel=1.4 -dPDFSETTINGS=/ebook -dNOPAUSE -q -sDEVICE=pdfwrite -dDetectDuplicateImages -dCompressFonts=true -r150 -sOutputFile=$OUTPUT *.pdf
# gs -dBATCH -dCompatibilityLevel=1.4 -dPDFSETTINGS=/printer -dNOPAUSE -q -sDEVICE=pdfwrite -dDetectDuplicateImages -dCompressFonts=true -r150 -sOutputFile=$OUTPUT *.pdf
# gs -dBATCH -dCompatibilityLevel=1.4 -dPDFSETTINGS=/prepress -dNOPAUSE -q -sDEVICE=pdfwrite -dDetectDuplicateImages -dCompressFonts=true -r150 -sOutputFile=$OUTPUT *.pdf

qpdf --empty --pages *.pdf -- $OUTPUT
