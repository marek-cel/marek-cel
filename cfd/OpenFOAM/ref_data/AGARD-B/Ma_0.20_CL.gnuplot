set terminal png
set output "Ma_0.20_CL.png"
set xlabel "Angle of Attack [deg]"
set ylabel "Lift Coefficient [-]"
set xrange [0: 20]
set yrange [0.0: 1.2]
set xtics 10
set ytics nomirror
set key left top
set grid
set yzeroaxis lw 2
set style line 1 lc rgb '#ff0000' lw 2 pt 1 ps 0
set style line 2 lc rgb '#0000ff' lw 2 pt 1 ps 0
set style line 3 lc rgb '#00ff00' lw 2 pt 1 ps 0
set style line 4 lc rgb '#000000' lw 2 pt 1 ps 0
set datafile separator ","
plot \
  "AEDC-TR-70-100/Ma_0.20.csv" using 1:2 with linespoints ls 1 title "AEDC-TR-70-100",
