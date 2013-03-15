#ifndef FAST_FINITE_DIFFERENCE_H_
#define FAST_FINITE_DIFFERENCE_H_

#include "Algorithm.h"

/**
 * @class							Fast_Finite_Difference
 * @brief							An optimised version of Finite_Difference
 */
class Fast_Finite_Difference: public Algorithm {
public:

	/**
	 * @function					Constructor
	 * @brief						Creates a ffd object from a requested grid
	 * @param						Grid : entry
	 * @return						None
	 */
	Fast_Finite_Difference(Grid entry);
	virtual ~Fast_Finite_Difference();

	/**
	 * @function					get_solution
	 * @brief						calls the solve function to run the algorithm and obtains the solution
	 * @return						Grid : solution of grid
	 */
	Grid get_solution();
private:

	/**
	 * @function					solve
	 * @brief						Runs the ffd algorithm on the grid
	 * @return						None
	 */
	void solve();
};

#endif /* FAST_FINITE_DIFFERENCE_H_ */
