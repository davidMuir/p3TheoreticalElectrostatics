#include "../Structures/Grid.h"

/*

	This is a solution I came up with myself. It's based on the principles of
	the finite volume method but is a bit peculiar since it is asymmetric:
	the order in which you loop over the grid actually makes a difference,
	although the limit when its -> inf is the same. Essentially we keep a limited
	number of total "volume" (value) in the grid, except at the boundary points
	which work as sources or sinks. Due to some "clever" techniques
	it also takes into account whether or not a certain cell is accessible or not,
	and normalises for this. Hence we can define a new special type of
	boundary that is inaccessible. This can be thought of as an area that is
	as if submerged in flowing water: the water acknowledges it and flows around it,
	but it does not work as a source or sink.

	//Karl

*/

using namespace std;

//This is duplicated for now until I can find a reasonably sensible place for this
struct Iteration {

	matrix it;
	double error;

};

double average_value(vector<Value> vec) {
	double total = 0;
	for (int i = 0; i < vec.size(); i++) {
		total += vec[i].value;
	}
	return total / vec.size();
}

double total_value(vector<Value> vec) {
	double total = 0;
	for (int i = 0; i < vec.size(); i++) {
		total += vec[i].value;
	}
	return total;
}

double total_value(vector<double> vec) {
	double total = 0;
	for (int i = 0; i < vec.size(); i++) {
		total += vec[i];
	}
	return total;
}

double average_value(vector<double> vec) {
	double total = 0;
	for (int i = 0; i < vec.size(); i++) {
		total += vec[i];
	}
	return total / vec.size();
}

class Asymmetric_Finite_Volume {

	private:

	//Just some stuff used later on. Precision and maxit determine the
	//conditions of the solution

	Grid grid;
	Grid solution;
	double precision;
	unsigned int maxit;
	unsigned int its;

	//Internal function for updating to the next iteration

	Iteration iteration(Iteration old) {
		matrix m = old.it;
		unsigned int no = m.size();
		unsigned int mo = m[0].size();
		double change = 0;
		vector<Value> cells;
		vector<double> dv;
		double old_value;
		double DV;
		double coefficient;
		double total_difference;
		unsigned int count;
		for(int x = 1; x < no-1; x++) {
			for(int y = 1; y < mo-1; y++) {
				old_value = m[x][y].value;
				if(m[x-1][y].accessible == true){
				cells.push_back(m[x-1][y]);
				dv.push_back(m[x][y].value - m[x-1][y].value);
				}
				if(m[x+1][y].accessible == true){
				cells.push_back(m[x+1][y]);
				dv.push_back(m[x][y].value - m[x+1][y].value);
				}
				if(m[x][y-1].accessible == true){
				cells.push_back(m[x][y-1]);
				dv.push_back(m[x][y].value - m[x][y-1].value);
				}
				if(m[x][y+1].accessible == true){
				cells.push_back(m[x][y+1]);
				dv.push_back(m[x][y].value - m[x][y+1].value);
				}
				cells.push_back(m[x][y]);
				double average = average_value(cells);
				if(m[x][y].boundary == false)m[x][y].value = average;
				DV = average - old_value;
				if(abs(DV) > change)change = abs(DV);
				total_difference = total_value(dv);
				if(total_difference == 0 || DV == 0)continue; //Bad luck!
				coefficient = -DV/total_difference;
				count = 0;
				if(m[x-1][y].accessible == true){if(m[x-1][y].boundary == false){m[x-1][y].value = m[x-1][y].value + coefficient * dv[count];} count++;}
				if(m[x+1][y].accessible == true){if(m[x+1][y].boundary == false){m[x+1][y].value = m[x+1][y].value + coefficient * dv[count];} count++;}
				if(m[x][y-1].accessible == true){if(m[x][y-1].boundary == false){m[x][y-1].value = m[x][y-1].value + coefficient * dv[count];} count++;}
				if(m[x][y+1].accessible == true){if(m[x][y+1].boundary == false){m[x][y+1].value = m[x][y+1].value + coefficient * dv[count];} count++;}
				cells.clear();
				dv.clear();
			}
		}
		Iteration next;
		next.it = m;
		next.error = change;
		return next;
	}
	
	public:

	//Takes the grid to be solved

	void to_solve(Grid entry) {
		grid = entry;
		maxit = 10000;
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
		solution.set_gradients(grid.get_gradients());
		its = k;
	}

	//Return solution / number of iterations required to get it

	Grid get_solution() {return solution;}
	unsigned int number_of_iterations() {return its;}

	};
