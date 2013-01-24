reset

set dgrid3d
set contour base
set cntrparam level incremental -100, 2, 100
unset surface
set table 'contour.dat'
splot 'data.dat' matrix
unset table

reset
set xrange [0:100]
set yrange [0:100]
unset key
set cbrange [-100:100]
set palette color
set palette defined
set term postscript
set output '../plots/halfcircle.ps'
set view equal xy
p 'data.dat' matrix with image #, 'contour.dat' w l lt -1 lw 0.5
