//Wrapper for placing several conductors in the same field
//AUTHOR: KARL

#ifndef CONDUCTORS_H_
#define CONDUCTORS_H_

#include "../Structures/Grid.h"
#include "../Algorithms/Fast_Finite_Difference.h"
#include "../Algorithms/Finite_Difference.h"
#include "../Algorithms/Asymmetric_Finite_Volume.h"

struct Conductor {
	int x;
	int y;
	int dx;
	int dy;
	Shape shape;
};

class Conductors {
	public:
	Conductors();
	Conductors(unsigned int x, unsigned int y, double l, double r);
	~Conductors();

	void new_conductor(int x, int y, int dx, int dy, Shape shape);
	Grid get_solution(Algo algorithm);

	void set_precision(double prec);
	void set_maxit(int max);

	private:
	vector<Grid> _grids;
	vector<Grid> _solutions;
	vector<Conductor> _conductors;
	Grid _solution;
	void solve();
	unsigned int _x_size, _y_size;
	double _left, _right;
	int _order;
	double _precision;
	int _maxit;
};

#endif /* CONDUCTORS_H_ */
