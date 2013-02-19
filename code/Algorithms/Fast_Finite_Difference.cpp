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
	matrix *current, *alternate;
	current = &one;
	alternate = &two;
	double error = 1000;
	double betaSq = beta*beta;
	int n = current->size();
	int m = (*current)[0].size();
	for (its = 0;error > precision && its < maxit;its++) {
		error = 0;
		matrix *temp = current;
		current = alternate;
		alternate = temp;
		for (int x = 0; x < n-1; x++) {
			for (int y = 0; y < m-1; y++) {
				if (!(*current)[x][y].boundary) {
					(*alternate)[x][y].value = (
							(*current)[x-1][y].value + (*current)[x+1][y].value +
							betaSq*((*current)[x][y-1].value + (*current)[x][y+1].value))/
							(2*(1+betaSq));
					if (std::abs((*alternate)[x][y].value - (*current)[x][y].value) > error)
						error = std::abs((*alternate)[x][y].value-(*current)[x][y].value);
				}
			}
		}
		grid.set_values(one);
	}
}
Grid Fast_Finite_Difference::get_solution() {
	Fast_Finite_Difference::solve();
	return grid;
}
