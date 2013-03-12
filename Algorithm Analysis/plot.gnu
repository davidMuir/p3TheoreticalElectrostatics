set terminal postscript
set output './fd_ffd_comparison_fit.ps'
set title 'Comparison between fd and ffd'
set xlabel 'Number of Grid Elements'
set ylabel 'Runtime (seconds)'
f(x) = a*x + b
g(x) = c*x + d
fit f(x) './fd_ffd_comparison.dat' u 1:2 via a,b
fit g(x) './fd_ffd_comparison.dat' u 1:3 via c,d
plot './fd_ffd_comparison.dat' u 1:2 t 'fd','./fd_ffd_comparison.dat' u 1:3 t 'ffd', f(x) t 'fd', g(x) t 'ffd'
