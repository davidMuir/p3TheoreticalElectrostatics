reset

reset
set xrange [0:50]
set yrange [0:50]
unset key
set cbrange [-50:50]
set palette color
set palette defined
set term postscript
set output "./plots/script.ps"
set view equal xy
p './data/results_new.dat' matrix with image
