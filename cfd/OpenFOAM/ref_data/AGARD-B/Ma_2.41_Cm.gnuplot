set terminal png
set output "Ma_2.41_Cm.png"
set xlabel "Angle of Attack [deg]"
set ylabel "Pitching Moment Coefficient [-]"
set xrange [0: 6]
set yrange [0.0: 0.06]
set xtics 1
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
  "NACA-TN-3300/Ma_2.41_Cm.csv" using 1:2 with linespoints ls 1 title "NACA-TN-3300", \
  "OpenFOAM/Ma_2.41_Cm.csv" using 1:2 with linespoints ls 2 title "OpenFOAM",
