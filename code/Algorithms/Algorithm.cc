#include "Algorithm.h"

/*
 * Algorithm.cpp
 *
 *  Created on: 3 Feb 2013
 *      Author: david
 */

Algorithm::Algorithm(Grid entry) {
	grid = entry;
	beta = std::abs(grid.get_coordinates()[0][0].get_x() - grid.get_coordinates()[1][0].get_x())/
			std::abs(grid.get_coordinates()[0][0].get_y() - grid.get_coordinates()[0][1].get_y());
	maxit = 5000;
	precision = 1;
}

Algorithm::~Algorithm() {
}

void Algorithm::set_precision(double prec) {precision = prec;}
void Algorithm::set_maxit(unsigned int max) {maxit = max;}
unsigned int Algorithm::get_iterations() {return its;}

