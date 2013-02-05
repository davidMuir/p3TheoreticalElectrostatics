reset

set dgrid3d
set contour base
set cntrparam level incremental -100, 2, 100
unset surface
set table 'contour.dat'
splot 'data.dat' matrix
unset table

reset
set xrange [0:50]
set yrange [0:50]
unset key
set cbrange [-50:50]
set palette color
set palette defined
set term postscript
set output '../plots/newtest.ps'
set view equal xy
p 'results_new.dat' matrix with image #, 'contour.dat' w l lt -1 lw 0.5
