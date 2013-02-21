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
#include <assert.h>
#include "Coordinate.h"

enum Shape {circle, semicircle_north, semicircle_south, semicircle_east,
	semicircle_west, rectangle, triangle, ellipse, star, random_shape};

//Data structures to be used for grid
struct Value {
	double value;
	bool boundary;
	bool accessible;
	int flag;
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
	void set_boundary_point(unsigned int x, unsigned int y, bool bound);
	void set_boundary_value(unsigned int x, unsigned int y, double val);
	void set_boundary_value_float(double xd, double yd, double val);
	void set_flow(double left, double right);
	void set_coordinates(coordinate_matrix coords);
	void set_values(matrix vals);
	void set_gradients(grad_matrix grads);
	void equip_values(int n, int xmax, int ymax, double Emax, int line_width, int menu);
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
	void set_boundary_shape(int x1, int y1, int r, int z, double val,
			Shape shape, int x2=0, int x3 = 0, int x4 = 0, int y2 = 0, int y3 = 0, int y4 = 0);
	Grid get_boundary_grid(int size_x, int size_y, int x, int y, int dx, int dy, Shape shape);
	//Solving
	void efield();
private:
	//private members
	coordinate_matrix points;
	grad_matrix gradients;
	matrix values;
	//private functions
	int round_own(double a);
	void check_and_mark_cells (int &xa, int &ya, int deltax, int deltay, Value &prev_prev2, Value &prev2, Value &current2);
	bool compare(Value nn, Value mm);

};


#endif /* GRID_H_ */
