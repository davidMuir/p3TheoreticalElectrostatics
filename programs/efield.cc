#include "../code/Algorithms/Asymmetric_Finite_Volume.h"
#include "../code/Utils/Gnuplot.h"
#include "../code/Algorithms/Finite_Difference.h"
#include "../code/Algorithms/Fast_Finite_Difference.h"
#include "../code/Errors/Compare.h"
#include "../code/Utils/Animation.h"
#include "../code/Utils/Conductors.h"
#include "../code/Structures/Grid.h"
#include <ctime>

using namespace std;


int main() {

	int n = 100;
	int m = 100;

	double Emax=100;
	double Emin=-100;

	Grid first_grid(n,m);

	first_grid.set_flow(Emax, Emin);
	first_grid.set_boundary_shape(50,50,20,0,0,circle);
	first_grid.print_figure_to("figure.dat");

	Finite_Difference fd (first_grid);
	fd.set_precision(0.00001);
	fd.set_maxit(10000);
   	Grid sol = fd.get_solution();

	sol.alternative_efield(5,1);  //(density,length)
	sol.print_all_to("results.dat");

	Gnuplot gp(sol);
	gp.add_command("set term postscript");
	gp.add_command("set ytics ('100' 100)");
   	gp.add_command("set xtics ('100' 100)");
	gp.add_command("set output 'efield.ps'");
	gp.add_command("unset key");
	gp.add_command("set palette color");
	gp.add_command("set palette defined");
	gp.add_command("plot 'results.dat' using 1:2:6 with image, 'results.dat' with vectors ls -1, 'figure.dat' with filledcurve ls -1");
	gp.sendString();

	return 0;
 
}

