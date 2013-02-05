#ifndef FINDIF_H_
#define FINDIF_H_

#include "Algorithm.h"

class Finite_Difference : public Algorithm {
public:
	Finite_Difference(Grid entry);
	~Finite_Difference();
	//Getters and setters
	Grid get_solution();
	unsigned int get_iterations();
private:
	Iteration iteration(Iteration old);
	void solve();
};

#endif /* FINDIF_H_ */
