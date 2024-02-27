PLOTFILES = \
	Ma_0.20_CD.gnuplot \
	Ma_0.20_CL.gnuplot \
	Ma_0.20_Cm.gnuplot \
	Ma_1.00_CD.gnuplot \
	Ma_1.00_CL.gnuplot \
	Ma_1.00_Cm.gnuplot \
	Ma_1.62_CD.gnuplot \
	Ma_1.62_CL.gnuplot \
	Ma_1.62_Cm.gnuplot \
	Ma_2.41_CD.gnuplot \
	Ma_2.41_CL.gnuplot \
	Ma_2.41_Cm.gnuplot

all: $(PLOTFILES:.gnuplot=.png)


.SUFFIXES: .gnuplot .png

.gnuplot.png:
	gnuplot $*.gnuplot

clean:
	rm -f *.png
