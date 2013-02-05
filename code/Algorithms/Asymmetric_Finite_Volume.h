#ifndef ASYM_H_
#define ASYM_H_

#include "Algorithm.h"

/*

	This is a solution I came up with myself. It's based on the principles of
	the finite volume method but is a bit peculiar since it is asymmetric:
	the order in which you loop over the grid actually makes a difference,
	although the limit when its -> inf is the same. Essentially we keep a limited
	number of total "volume" (value) in the grid, except at the boundary points
	which work as sources or sinks. Due to some "clever" techniques
	it also takes into account whether or not a certain cell is accessible or not,
	and normalises for this. Hence we can define a new special type of
	boundary that is inaccessible. This can be thought of as an area that is
	as if submerged in flowing water: the water acknowledges it and flows around it,
	but it does not work as a source or sink.

	//Karl

*/

using namespace std;

class Asymmetric_Finite_Volume : public Algorithm {
public:
	Asymmetric_Finite_Volume(Grid entry);
	~Asymmetric_Finite_Volume();
	//Getters and setters
	Grid get_solution();
	unsigned int get_iterations();
private:
	Iteration iteration(Iteration old);
	void solve();
};

#endif /* ASYM_H_ */
