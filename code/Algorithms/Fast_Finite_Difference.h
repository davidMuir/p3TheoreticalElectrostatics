/*
 * FiniteDifference.h
 *
 *  Created on: 19 Feb 2013
 *      Author: david
 */

#ifndef FAST_FINITE_DIFFERENCE_H_
#define FAST_FINITE_DIFFERENCE_H_

#include "Algorithm.h"

#define THREADS std::thread::hardware_concurrency()

class Fast_Finite_Difference: public Algorithm {
public:
	Fast_Finite_Difference();
	Fast_Finite_Difference(Grid entry);
	virtual ~Fast_Finite_Difference();
	Grid get_solution();
//	int get_iterations();
private:
	void solve();
};

#endif /* FAST_FINITE_DIFFERENCE_H_ */
