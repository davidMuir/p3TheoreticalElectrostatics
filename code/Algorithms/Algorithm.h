<<<<<<< HEAD
=======
/*
 * Algorithm.h
 *
 *  Created on: 3 Feb 2013
 *      Author: david
 */

>>>>>>> cd38be1918a97e584f159577f49088c2cf0819c7
#ifndef ALGORITHM_H_
#define ALGORITHM_H_

#include "../Structures/Grid.h"
#include "../Utils/Utils.h"

struct Iteration {

	matrix it;
	double error;

};

class Algorithm {
public:
	Algorithm();
	Algorithm(Grid entry);
	virtual ~Algorithm();
	void to_solve(Grid entry);
	void set_precision(double prec);
	void set_maxit(unsigned int max);
	Grid get_solution();
	unsigned int get_iterations();
protected:
	Grid grid;
	Grid solution;
	double beta;
	double precision;
	unsigned int maxit;
	unsigned int its;
	Iteration iteration(Iteration old);
	void solve();
};

#endif /* ALGORITHM_H_ */