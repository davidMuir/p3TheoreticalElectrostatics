#include "Algorithm3d.h"

Algorithm3d::Algorithm3d(Grid3d entry) {
       grid = entry;
	beta_y = std::abs(grid.get_coordinates()[0][0][0].get_x() - grid.get_coordinates()[1][0][0].get_x())/
			std::abs(grid.get_coordinates()[0][0][0].get_y() - grid.get_coordinates()[0][1][0].get_y());
	beta_z = std::abs(grid.get_coordinates()[0][0][0].get_x() - grid.get_coordinates()[1][0][0].get_x())/
	  std::abs(grid.get_coordinates()[0][0][0].get_z() - grid.get_coordinates()[0][0][1].get_z());
	maxit = 5000;
	precision = 1;
}

Algorithm3d::~Algorithm3d() {
}

void Algorithm3d::set_precision(double prec) {precision = prec;}
void Algorithm3d::set_maxit(unsigned int max) {maxit = max;}
unsigned int Algorithm3d::get_iterations() {return its;}
