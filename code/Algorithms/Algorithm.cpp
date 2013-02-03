/*
 * Algorithm.cpp
 *
 *  Created on: 3 Feb 2013
 *      Author: david
 */

#include "Algorithm.h"

Algorithm::Algorithm(Grid entry) {
	grid = entry;
			beta = std::abs(grid.get_coordinates()[0][0].get_x() - grid.get_coordinates()[1][0].get_x())/
					std::abs(grid.get_coordinates()[0][0].get_y() - grid.get_coordinates()[0][1].get_y());
			maxit = 5000;
			precision = 1;
}

Algorithm::~Algorithm() {
	// TODO Auto-generated destructor stub
}

