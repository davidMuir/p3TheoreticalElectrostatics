reset

set terminal postscript
set output './comparison_wc.ps'
set xrange[0:30000]
set ytics 50 nomirror
set y2tics 1 nomirror

set title 'Comparison of Worst-Case performances'
set xlabel 'Number of Grid Elements'
set ylabel 'Runtime (seconds)' tc lt 1
set y2label 'Runtime (seconds)' tc rgb "blue" 
set yrange [0:200]
set y2range [0:5]

set style line 1 lt 1 lc 1
set style line 2 lt 2 lc 2
set style line 3 lt 3 lc 2

f(x) = a*x + b
g(x) = c*x + d
h(x) = e*x + f
fit f(x) './fd_ffd_comparison_wc.dat' u 1:2 via a,b
fit g(x) './fd_ffd_comparison_wc.dat' u 1:3 via c,d
fit h(x) './afv_wc.dat' u 1:2 via e,f
plot './fd_ffd_comparison_wc.dat' u 1:2 notitle axes x1y2, f(x) t 'fd' linetype 1 lc 3 axes x1y2,\
'./fd_ffd_comparison_wc.dat' u 1:3 notitle linetype 2 axes x1y2, g(x) t 'ffd' linetype 2 lc 3 axes x1y2,\
'./afv_wc.dat' u 1:2 notitle linetype 3, h(x) t 'afv' linetype 1 lc 1
