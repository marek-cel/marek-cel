PLOTFILES = \
	CL.gnuplot \
	CL_90.gnuplot \
	CD.gnuplot \
	CD_90.gnuplot \
	Cm.gnuplot \
	Cm_90.gnuplot

all: $(PLOTFILES:.gnuplot=.png)


.SUFFIXES: .gnuplot .png

.gnuplot.png:
	gnuplot $*.gnuplot

clean:
	rm -f *.png
