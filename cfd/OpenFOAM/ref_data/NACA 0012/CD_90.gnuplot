set terminal png
set output "CD_90.png"
set xlabel "Angle of Attack [deg]"
set ylabel "Drag Coefficient [-]"
set xrange [0: 90]
set yrange [0.0: 2.2]
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
  "NACA TN-3361/CD.csv" using 1:2 with linespoints ls 1 title "NACA TN-3361", \
  "Sandia Labs/CD_90.csv" using 1:2 with linespoints ls 2 title "Sandia Labs", \
  "OpenFOAM/CD.csv" using 1:2 with linespoints ls 4 title "OpenFOAM",
