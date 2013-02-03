/*
 * Algorithm.h
 *
 *  Created on: 3 Feb 2013
 *      Author: david
 */

#ifndef ALGORITHM_H_
#define ALGORITHM_H_

class Algorithm {
public:
	Algorithm(Grid entry);
	virtual ~Algorithm();
	void to_solve(Grid entry)
	void set_precision(double prec);
	void set_maxit(unsigned int max);
	void solve();
	Grid get_solution();
	unsigned int number_of_iterations();
protected:
	Grid grid;
	Grid solution;
	double beta;
	double precision;
	unsigned int maxit;
	unsigned int its;
	Iteration iteration(Iteration old);
};

#endif /* ALGORITHM_H_ */
