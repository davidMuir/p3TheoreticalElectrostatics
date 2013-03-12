#include "Algorithms/Asymmetric_Finite_Volume.h"
#include "Utils/Gnuplot.h"
#include "Algorithms/Finite_Difference.h"
#include "Algorithms/Fast_Finite_Difference.h"
#include "Errors/Compare.h"
#include "Utils/Conductors.h"
#include <ctime>

using namespace std;

int main() {

	int N = 11 ;     // number of eq.p. lines
	int n = 200;
	int m = 200;


	double Emax=50;
	double Emin=-50;

	Grid first_grid(n,m);

	first_grid.set_flow(Emax, Emin);
	first_grid.set_conductor(100,100,30,0,circle);

	first_grid.print_figure_to("figure.dat", 1);

	Finite_Difference fd (first_grid);
	fd.set_precision(0.00001);
	fd.set_maxit(10000);
    Grid sol = fd.get_solution();
	sol.print_all_to("results.dat");


	Gnuplot gp(sol);
	sol.equip_values(N,n,m,Emax,1,1);
	sol.print_contours_to("eq_lines.dat", N);


	gp.add_command("set term postscript");
    gp.add_command("set ytics ('200' 200)");
    gp.add_command("set xtics ('200' 200)");
	gp.add_command("set output 'first_plot.ps'");
	gp.add_command("set palette defined");
    gp.add_command("unset key");
	gp.add_command("plot 'results.dat' with image, 'eq_lines.dat' with lines ls -1, 'figure.dat' with lines ls -1"); // white = ls -3; black = ls -1; red = ls 1; green = 2; blue = ls 3; violet = ls 4;
	gp.sendString();

	return 0;

	}
