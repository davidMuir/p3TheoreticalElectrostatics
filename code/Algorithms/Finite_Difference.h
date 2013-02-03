#include "Algorithm.h"

class Finite_Difference : public Algorithm {
public:
	Finite_Difference(Grid entry);
	~Finite_Difference();
	//Getters and setters
	void set_precision(double prec);
	void set_maxit(unsigned int max);
	Grid get_solution();
	unsigned int get_iterations();
private:
	Iteration iteration(Iteration old);
	void solve();
};
