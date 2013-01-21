#include "finite_difference.h"

using namespace std;

int main() {

	Grid first_grid;
	first_grid.load_grid(100,100);
	first_grid.set_range(10, 10);
	first_grid.set_boundary_value(50,50,100);
	//first_grid.print_values();

	/*
	Coordinate one;
	Coordinate two;
	one.set_x(1);
	one.set_y(2);
	two.set_x(10);
	two.set_y(-10);
	cout << one.distance(two) << endl;
	*/

	Finite_Difference fd;
	fd.to_solve(first_grid);
	fd.set_precision(0);
	fd.solve();
	Grid sol = fd.get_solution();
	sol.gnuplot_values();

	return 0;

	}
