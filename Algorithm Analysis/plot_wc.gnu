reset

set terminal postscript
set output './comparison_wc.ps'
set xrange[0:30000]
set ytics 50 nomirror
set y2tics 1 nomirror

set title 'Comparison of Worst-Case performances'
set xlabel 'Number of Grid Elements'
set ylabel 'Runtime (seconds) -- Finite Volume Method' tc lt 1
set y2label 'Runtime (seconds) -- Finite Difference methods' tc lt 2
set yrange [0:200]
set y2range [0:5]

f(x) = a*x + b
g(x) = c*x + d
h(x) = e*x + f
fit f(x) './fd_ffd_comparison_wc.dat' u 1:2 via a,b
fit g(x) './fd_ffd_comparison_wc.dat' u 1:3 via c,d
fit h(x) './afv_wc.dat' u 1:2 via e,f
plot './fd_ffd_comparison_wc.dat' u 1:2 notitle linetype 1 axes x1y2, f(x) t 'fd' linetype 2 axes x1y2,\
'./fd_ffd_comparison_wc.dat' u 1:3 notitle linetype 2 axes x1y2, g(x) t 'ffd' linetype 3 axes x1y2,\
'./afv_wc.dat' u 1:2 notitle linetype 2, h(x) t 'afv' linetype 1
