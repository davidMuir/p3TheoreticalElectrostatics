#include "Algorithms/Asymmetric_Finite_Volume.h"

using namespace std;

int main() {

	int n = 50;
	int m = 50;

	Grid first_grid(n,m);
	first_grid.set_flow(50, -50);
	first_grid.set_circle_noflow(25,25,10,100);

	Asymmetric_Finite_Volume fd;
	fd.to_solve(first_grid);
	fd.set_precision(0.2);
	fd.set_maxit(10000);
	fd.solve();
	Grid sol = fd.get_solution();
	//cout << fd.number_of_iterations() << endl;
	//	sol.gnuplot_values();
	sol.efield();
	sol.print_all_to("results.dat");
	

	return 0;

	}
