#include "Conductors.h"

using namespace std;

Conductors::Conductors() :
	Conductors::Conductors(50,50, -50., 50.) {
}

Conductors::Conductors(unsigned int x, unsigned int y, double l, double r) {
	_x_size = x;
	_y_size = y;
	_left = l;
	_right = r;
	_order = 0;
	_precision = 0.001;
	_maxit = 5000;
}

Conductors::~Conductors() {
}

void Conductors::new_conductor(int x, int y, int dx, int dy, Shape shape) {
	Conductor cond;
	cond.x = x;
	cond.y = y;
	cond.dx = dx;
	cond.dy = dy;
	cond.shape = shape;
	_conductors.push_back(cond);
	Grid new_grid(_x_size, _y_size);
	new_grid.set_flow(_left, _right);
	_grids.push_back(new_grid);
	_grids[_order].set_conductor(x, y, dx, dy, shape);
	_order++;
}

Grid Conductors::get_solution(Algo algorithm) {
	for(int it = 0; it < _grids.size(); it++) {
		Finite_Difference algo(_grids[it]);
		switch (algorithm) {

		case FD: {
			Finite_Difference algo(_grids[it]);
		}

		case FFD: {
			Fast_Finite_Difference algo(_grids[it]);
		}

		case AFV: {
			Asymmetric_Finite_Volume algo(_grids[it]);
		}
		}//end switch

		algo.set_precision(_precision);
		algo.set_maxit(_maxit);
		Grid sol = algo.get_solution();
		_solutions.push_back(sol);
	}
	Grid dummy(_x_size, _y_size);
	matrix total = dummy.get_values();
	for(int it1 = 0; it1 < _solutions.size(); it1++) {
		matrix temp = _solutions[it1].get_values();
		for(int xs = 0; xs < _x_size + 1; xs++) {
			for(int ys = 0; ys < _y_size + 1; ys++) {
				total[xs][ys].value += temp[xs][ys].value;
			}
		}
	}
	for(int xs1 = 0; xs1 < _x_size + 1; xs1++) {
		for(int ys1 = 0; ys1 < _y_size + 1; ys1++) {
			total[xs1][ys1].value /= _solutions.size();
		}
	}
	dummy.set_values(total);
	for(int it2 = 0; it2 < _conductors.size(); it2++) {
		int x1 = _conductors[it2].x;
		int y1 = _conductors[it2].y;
		int dx1 = _conductors[it2].dx;
		int dy1 = _conductors[it2].dy;
		Shape shape1 = _conductors[it2].shape;
		dummy.set_conductor(x1, y1, dx1, dy1, shape1);
	}
	Finite_Difference algo1(dummy);
	switch (algorithm) {

	case FD: {
		Finite_Difference algo1(dummy);
	}

	case FFD: {
		Fast_Finite_Difference algo1(dummy);
	}

	case AFV: {
		Asymmetric_Finite_Volume algo1(dummy);
	}
	}//end switch
	algo1.set_precision(_precision);
	algo1.set_maxit(_maxit);
	_solution = algo1.get_solution();
	return _solution;
}

void Conductors::set_precision(double prec) {
	_precision = prec;
}

void Conductors::set_maxit(int max) {
	_maxit =  max;
}
