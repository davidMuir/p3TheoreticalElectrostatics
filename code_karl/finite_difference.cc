#include "include/finite_difference.h"

using namespace std;

int main() {

	int n = 100;
	int m = 100;

	Grid first_grid;
	first_grid.load_grid(n,m);
	first_grid.set_flow(100, -100);
	first_grid.set_ellipse(50,50,20,10,0);

	Finite_Difference fd;
	fd.to_solve(first_grid);
	fd.set_precision(0);
	fd.solve();
	fd.efield();
	Grid sol = fd.get_solution();
	sol.print_dxdy();




	return 0;

	}
