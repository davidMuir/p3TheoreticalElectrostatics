#include "include/finite_difference.h"

using namespace std;

int main() {

	int n = 100;
	int m = 100;

	Grid first_grid;
	first_grid.load_grid(n,m);
	first_grid.set_flow(100, -100);
	first_grid.set_halfcircle_north(50,50,20,0);

	Finite_Difference fd;
	fd.to_solve(first_grid);
	fd.set_precision(0);
	fd.solve();
	Grid sol = fd.get_solution();
	//cout << fd.number_of_iterations() << endl;
	sol.gnuplot_values();
	

	return 0;

	}
