TEX_FILES=\
	document.tex

BIB_FILES=\
	document.bib

################################################################################

.SUFFIXES: .bib .bbl
.SUFFIXES: .tex .aux
.SUFFIXES: .tex .pdf

all: $(TEX_FILES:.tex=.aux) $(BIB_FILES:.bib=.bbl) $(TEX_FILES:.tex=.pdf)

.bib.bbl: $(BIB_FILES)
	@bibtex $*

.tex.aux: $(TEX_FILES)
	@latex $*.tex

# .tex.pdf: $(TEX_FILES)
# 	@latex $*.tex
# 	@latex $*.tex
# 	@dvipdf $*.dvi

.tex.pdf: $(TEX_FILES)
	@latex $*.tex
	@pdflatex $*.tex

################################################################################

clean:
	@rm -f *.aux
	@rm -f *.bbl
	@rm -f *.blg
	@rm -f *.log
	@rm -f *.out
	@rm -f *.run.xml
	@rm -f *.toc
	@rm -f *.fdb_latexmk
	@rm -f *.fls

cleanall: clean
	@rm -f *.dvi
	@rm -f *.pdf
