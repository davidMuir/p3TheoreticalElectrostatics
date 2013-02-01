reset
f(x,y)=(100/sqrt(x**2 + y**2)-sqrt(x**2 + y**2))*0.2*x/sqrt(x**2 + y**2)

set xrange [-50:50]
set yrange [-50:50]
set isosample 1000, 1000
set table 'data.dat'
splot f(x,y)
unset table

set contour base
set cntrparam level incremental -10, 2, 10
unset surface
set table 'contour.dat'
splot f(x,y)
unset table

reset
set xrange [-50:50]
set yrange [-50:50]
unset key
set cbrange [-10:10]
set palette defined (-10 "blue", 10 "red")
set term postscript
set output 'potential.ps'
set view equal xy
p 'data.dat' with image, 'contour.dat' w l lt -1 lw 0.5
