#include "Finite_Difference.h"

Finite_Difference::Finite_Difference(Grid entry) : Algorithm(entry)  {}

Finite_Difference::~Finite_Difference() {}

Iteration Finite_Difference::iteration(Iteration old)  {
	matrix mo = old.it;
	matrix newm = old.it;
	unsigned int n = mo.size();
	unsigned int m = mo[0].size();
	double change = 0;
	for(unsigned int x = 1; x < n-1; x++) {
		for(unsigned int y = 1; y < m-1; y++) {
			if(mo[x][y].boundary == false)
				{
				newm[x][y].value =
				(mo[x-1][y].value + mo[x+1][y].value + beta*beta*(mo[x][y-1].value + mo[x][y+1].value))/
				(2*(1+beta*beta));
				if(std::abs(newm[x][y].value - mo[x][y].value) > change)change = std::abs(newm[x][y].value - mo[x][y].value);
				}
			}
		}
	Iteration next;
	next.it = newm;
	next.error = change;
	return next;
}

void Finite_Difference::solve() {
	matrix first = grid.get_values();
	double err = 1000;
	unsigned int k = 1;
	Iteration o;
	Iteration n;
	o.it = first;
	o.error = err;
	while(err > precision && k < maxit) {
		n = iteration(o);
		err = n.error;
		o = n;
		k++;
	}
	solution.set_values(n.it);
	solution.set_coordinates(grid.get_coordinates());
	solution.set_gradients(grid.get_gradients());
	its = k;
}

unsigned int Finite_Difference::get_iterations() {
	return its;
}

Grid Finite_Difference::get_solution() {
	Finite_Difference::solve();
	return solution;
}
