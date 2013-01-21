#include "grid.h"

int main() {

	Grid first_grid;
	first_grid.load_grid(5,5);
	first_grid.set_range(100, 100);
	first_grid.set_value(2,1,1.5);
	first_grid.print_values();
	first_grid.print_points();
	return 0;

	}
