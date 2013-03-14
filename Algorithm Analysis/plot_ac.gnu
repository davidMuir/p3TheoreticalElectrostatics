reset

set terminal postscript
set output './comparison_ac.ps'
set xrange[0:200000]
set ytics 50 nomirror
set y2tics 10 nomirror

set title 'Comparison of Average-Case performances'
set xlabel 'Number of Grid Elements'
set ylabel 'Runtime (seconds)' tc lt 1
set y2label 'Runtime (seconds)' tc rgb "blue" 
set yrange [0:1000]
set y2range [0:50]

f(x) = a*x + b
g(x) = c*x + d
h(x) = e*x + f
fit f(x) './average_comparison.dat' u 1:2 via a,b
fit g(x) './average_comparison.dat' u 1:3 via c,d
fit h(x) './average_comparison.dat' u 1:4 via e,f
plot './average_comparison.dat' u 1:2 notitle linetype 1 axes x1y2, f(x) t 'fd' linetype 1 lc 3 axes x1y2,\
'./average_comparison.dat' u 1:3 notitle linetype 2 axes x1y2, g(x) t 'ffd' linetype 2 lc 3 axes x1y2,\
'./average_comparison.dat' u 1:4 notitle linetype 3, h(x) t 'afv' linetype 1 lc 1
