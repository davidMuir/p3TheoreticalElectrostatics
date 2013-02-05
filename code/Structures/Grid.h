/*
 * Grid.h
 *
 *  Created on: 2 Feb 2013
 *      Author: david
 */

#ifndef GRID_H_
#define GRID_H_

#include <cmath>
#include <iostream>
#include <vector>
#include <iomanip>
#include <fstream>
#include "Coordinate.h"

//Data structures to be used for grid
struct Value {
	double value;
	bool boundary;
	bool accessible;
};

struct Grad {
	double dx;
	double dy;
        double e_size;
};

typedef std::vector<std::vector<Value> > matrix;
typedef std::vector<std::vector<Coordinate> > coordinate_matrix;
typedef std::vector<std::vector<Grad> > grad_matrix;


class Grid {
public:
	//Constructors and destructors
	Grid();
	Grid(unsigned int x, unsigned int y);
	~Grid();
	//Getters and setters
	void set_range(double x, double y);
	void set_value(unsigned int x, unsigned int y, double val);
	void set_boundary(unsigned int x, unsigned int y, bool bound);
	void set_boundary_value(unsigned int x, unsigned int y, double val);
	void set_boundary_value_float(double xd, double yd, double val);
	void set_flow(double left, double right);
	void set_coordinates(coordinate_matrix coords);
	void set_values(matrix vals);
	void set_gradients(grad_matrix grads);
	coordinate_matrix get_coordinates();
	matrix get_values();
	grad_matrix get_gradients();
	//Printing
	void print_values();
	void print_points();
	void print_gnuplot_values();
	void print_all_to(std::string filename);
	void print_matrix_to(std::string filename);
	//Shapes -- These are just here temporarily, these should be moved to their own class/file
	void set_circle_noflow(int x, int y, unsigned int r, double val);
	void set_circle(int x, int y, unsigned int r, double val);
	void set_halfcircle_north(int x, int y, unsigned int r, double val);
	void set_halfcircle_south(int x, int y, unsigned int r, double val);
	void set_halfcircle_east(int x, int y, unsigned int r, double val);
	void set_halfcircle_west(int x, int y, unsigned int r, double val);
	void set_rectangle(int x1, int y1, int x2, int y2, double val);
	void set_isosceles(int x1, int x2, int y_base, int y_tip, double val);
	void set_ellipse(int x, int y, unsigned int rx, unsigned int ry,double val);
	//Solving
	void efield();
private:
	//private members
	coordinate_matrix points;
	grad_matrix gradients;
	matrix values;
	//private functions
	int round_own(double a);

};


#endif /* GRID_H_ */
