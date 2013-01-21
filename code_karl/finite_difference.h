#include "grid.h"

using namespace std;

struct Iteration {

	matrix it;
	double error;

	};

class Finite_Difference {

	private:
	Grid grid;
	Grid solution;
	double beta;
	double precision = 1;
	unsigned int maxit = 1000;
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
	void to_solve(Grid entry) {
		grid = entry;
		beta = (grid.get_coordinates()[0][0].get_x() - grid.get_coordinates()[1][0].get_x())/
				(grid.get_coordinates()[0][0].get_y() - grid.get_coordinates()[0][1].get_y());
		}

	void set_precision(double prec) {precision = prec;}

	void solve() {
		matrix first = grid.get_values();
		double err = 1000;
		unsigned int k = 0;
		Iteration o;
		Iteration n;
		o.it = first;
		o.error = err;
		while(err > precision) {
			n = iteration(o);
			err = n.error;
			o = n;
			k++;
			if(k > maxit)break;
			}
		solution.set_values(n.it);
		solution.set_coordinates(grid.get_coordinates());
		}

	Grid get_solution() {return solution;}

	};
