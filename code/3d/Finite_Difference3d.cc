#include "Finite_Difference3d.h"

Finite_Difference3d::Finite_Difference3d(Grid3d entry) : Algorithm3d(entry)  {
	grid = entry;
	beta_y = std::abs(grid.get_coordinates()[0][0][0].get_x() - grid.get_coordinates()[1][0][0].get_x())/
			std::abs(grid.get_coordinates()[0][0][0].get_y() - grid.get_coordinates()[0][1][0].get_y());
	beta_z = std::abs(grid.get_coordinates()[0][0][0].get_x() - grid.get_coordinates()[1][0][0].get_x())/
			std::abs(grid.get_coordinates()[0][0][0].get_z() - grid.get_coordinates()[0][0][1].get_z());
	maxit = 5000;
	precision = 1;
}

Finite_Difference3d::~Finite_Difference3d() {}

Iteration Finite_Difference3d::iteration(Iteration old)  {
  std::cout << "it" << std::endl;
	matrix3d mo = old.it;
	matrix3d newm = old.it;
	unsigned int n = mo.size();
	unsigned int m = mo[0].size();
	unsigned int p = mo[0][0].size();
	double change = 0;
	for(unsigned int x = 1; x < n-1; x++) {
	  for(unsigned int y = 1; y < m-1; y++) {
	    for(unsigned int z = 1; z < p-1; z++){
	      if(mo[x][y][z].boundary == false)
				{
				newm[x][y][z].value =
				  (mo[x-1][y][z].value + mo[x+1][y][z].value + beta_y*beta_y*(mo[x][y-1][z].value + mo[x][y+1][z].value)
				   + beta_z*beta_z*(mo[x][y][z-1].value + mo[x][y][z+1].value))/
				  (2*(1+beta_y*beta_y+beta_z*beta_z));
				if(std::abs(newm[x][y][z].value - mo[x][y][z].value) > change)change = std::abs(newm[x][y][z].value - mo[x][y][z].value);
				}
	    }
	  }
	} 
			
		
	Iteration next;
	next.it = newm;
	next.error = change;
	return next;
}

void Finite_Difference3d::solve() {
	matrix3d first = grid.get_values();
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

Grid3d Finite_Difference3d::get_solution() {
	Finite_Difference3d::solve();
	return solution;
}
