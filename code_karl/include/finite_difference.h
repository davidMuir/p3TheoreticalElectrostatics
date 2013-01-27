#include "grid.h"

using namespace std;

class Finite_Difference {

	private:

	//Just some stuff used later on. Precision and maxit determine the
	//conditions of the solution

	Grid grid;
	Grid solution;
	double beta;
	double precision;
	unsigned int maxit;
	unsigned int its;

	//Internal function for updating to the next iteration

	Iteration iteration(Iteration old) {
		matrix mo = old.it;
		matrix newm = old.it;
		unsigned int n = mo.size();
		unsigned int m = mo[0].size();
		double change = 0;
		for(int x = 1; x < n-1; x++) {
			for(int y = 1; y < m-1; y++) {
				if(mo[x][y].boundary == false)
					{
					newm[x][y].value = 
					(mo[x-1][y].value + mo[x+1][y].value + beta*beta*(mo[x][y-1].value + mo[x][y+1].value))/
					(2*(1+beta*beta));
					if(abs(newm[x][y].value - mo[x][y].value) > change)change = abs(newm[x][y].value - mo[x][y].value);
					}
				}
			}
		Iteration next;
		next.it = newm;
		next.error = change;
		return next;
		}

	public:

	//Takes the grid to be solved

	void to_solve(Grid entry) {
		grid = entry;
		beta = abs(grid.get_coordinates()[0][0].get_x() - grid.get_coordinates()[1][0].get_x())/
				abs(grid.get_coordinates()[0][0].get_y() - grid.get_coordinates()[0][1].get_y());
		maxit = 5000;
		precision = 1;
		}

	//Change convergence conditions. Precision decides how much the solution
	//must converge to be accepted, maxit the maximum number of iterations

	void set_precision(double prec) {precision = prec;}
	void set_maxit(unsigned int max) {maxit = max;}

	//Solve for given precision and maxit

	void solve() {
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
		its = k;
		}

	// works out -d(phi)/dx and -d(phi)/dy. Allows us to plot electric field in gnuplot with vector.
	// Assumes h=1, will need to be altered if we change increment size.
	void efield(){
	  matrix dxdy = solution.get_values();
	  for(int x=0; x<dxdy[0].size()-1; x++){
	    for(int y=0; y<dxdy[0].size()-1; y++){
	      dxdy[x][y].dx=dxdy[x][y].value-dxdy[x+1][y].value;
	      dxdy[x][y].dy=dxdy[x][y].value-dxdy[x][y+1].value;
	    }
	  }
	  solution.set_values(dxdy);
	}





	//Return solution / number of iterations required to get it

	Grid get_solution() {return solution;}
	unsigned int number_of_iterations() {return its;}

	};
