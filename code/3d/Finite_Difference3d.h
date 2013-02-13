#ifndef FINDIF3D_H_
#define FINDIF3D_H_

#include "Algorithm3d.h"

class Finite_Difference3d : public Algorithm3d {
public:
	Finite_Difference3d(Grid3d entry);
	~Finite_Difference3d();
	//Getters and setters
	Grid3d get_solution();
	unsigned int get_iterations();
private:
	Iteration iteration(Iteration old);
	void solve();
};

#endif /* FINDIF3D_H_ */
