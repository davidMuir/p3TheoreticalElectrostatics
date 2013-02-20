/*
 * FiniteDifference.cpp
 *
 *  Created on: 19 Feb 2013
 *      Author: david
 */

#include "Fast_Finite_Difference.h"

Fast_Finite_Difference::Fast_Finite_Difference(Grid entry) : Algorithm(entry) {}

Fast_Finite_Difference::~Fast_Finite_Difference() {}

void Fast_Finite_Difference::solve(){
	matrix one,two;
	one = two = grid.get_values();
	matrix *current, *alternate, *temp;
	current = &one;
	alternate = &two;
	bool error = 1;
	double betaSq = beta*beta;
	double divisor = 2*(1+betaSq);
	int n = current->size()-1;
	int m = (*current)[0].size()-1;
	for (its = 0;error && its < maxit;its++) {
		error = 0;
		temp = current;
		current = alternate;
		alternate = temp;
		for (int x = 1; x < n; x++) {
			for (int y = 1; y < m; y++) {
				if (!(*current)[x][y].boundary) {
					(*alternate)[x][y].value = (
							(*current)[x-1][y].value + (*current)[x+1][y].value +
							betaSq*((*current)[x][y-1].value + (*current)[x][y+1].value))/divisor;
					if (!error)
						error = std::abs((*alternate)[x][y].value - (*current)[x][y].value) > precision;
				}
			}
		}
	}
		grid.set_values(one);
}
Grid Fast_Finite_Difference::get_solution() {
	Fast_Finite_Difference::solve();
	return grid;
}
