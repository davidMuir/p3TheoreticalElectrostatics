#ifndef ALGORITHM3D_H_
#define ALGORITHM3D_H_

#include "Grid3d.h"
//#include "../Utils/Utils.h"

struct Iteration {

	matrix3d it;
	double error;

};

class Algorithm3d {
public:
        Algorithm3d();
	Algorithm3d(Grid3d entry);
	virtual ~Algorithm3d();
	void to_solve(Grid3d entry);
	void set_precision(double prec);
	void set_maxit(unsigned int max);
	Grid3d get_solution();
	unsigned int get_iterations();
protected:
	Grid3d grid;
	Grid3d solution;
	double beta_y;
	double beta_z;
	double precision;
	unsigned int maxit;
	unsigned int its;
	Iteration iteration(Iteration old);
	void solve();
};

#endif /*  ALGORITHM3D_H_ */
