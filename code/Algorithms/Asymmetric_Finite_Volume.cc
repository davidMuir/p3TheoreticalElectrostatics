#include "Asymmetric_Finite_Volume.h"

Asymmetric_Finite_Volume::Asymmetric_Finite_Volume(Grid entry) : Algorithm(entry)  {
	grid = entry;
	beta = std::abs(grid.get_coordinates()[0][0].get_x() - grid.get_coordinates()[1][0].get_x())/
			std::abs(grid.get_coordinates()[0][0].get_y() - grid.get_coordinates()[0][1].get_y());
	maxit = 5000;
	precision = 1;
}

Asymmetric_Finite_Volume::~Asymmetric_Finite_Volume() {}

Iteration Asymmetric_Finite_Volume::iteration(Iteration old) {
	matrix m = old.it;
	unsigned int no = m.size();
	unsigned int mo = m[0].size();
	double change = 0;
	vector<Value> cells;
	vector<double> dv;
	double old_value;
	double DV;
	double coefficient;
	double total_difference;
	unsigned int count;
	for(int x = 1; x < no-1; x++) {
		for(int y = 1; y < mo-1; y++) {
			old_value = m[x][y].value;
			if(m[x-1][y].accessible == true){
			cells.push_back(m[x-1][y]);
			dv.push_back(m[x][y].value - m[x-1][y].value);
			}
			if(m[x+1][y].accessible == true){
			cells.push_back(m[x+1][y]);
			dv.push_back(m[x][y].value - m[x+1][y].value);
			}
			if(m[x][y-1].accessible == true){
			cells.push_back(m[x][y-1]);
			dv.push_back(m[x][y].value - m[x][y-1].value);
			}
			if(m[x][y+1].accessible == true){
			cells.push_back(m[x][y+1]);
			dv.push_back(m[x][y].value - m[x][y+1].value);
			}
			cells.push_back(m[x][y]);
			double average = average_value(cells);
			if(m[x][y].boundary == false)m[x][y].value = average;
			DV = average - old_value;
			if(abs(DV) > change)change = abs(DV);
			total_difference = total_value(dv);
			if(total_difference == 0 || DV == 0) {
                if(m[x-1][y].accessible == true && m[x+1][y].accessible == true){
                    double xnew = (m[x-1][y].value + m[x+1][y].value) / 2.;
                    if(m[x-1][y].boundary == false){m[x-1][y].value = xnew;} if(m[x+1][y].boundary == false){m[x+1][y].value = xnew;}
                }
                if(m[x][y-1].accessible == true && m[x][y+1].accessible == true){
                    double ynew = (m[x][y-1].value + m[x][y+1].value) / 2.;
                    if(m[x][y-1].boundary == false){m[x][y-1].value = ynew;} if(m[x][y+1].boundary == false){m[x][y+1].value = ynew;}
                }
            }
			else {coefficient = -DV/total_difference;
                count = 0;
                if(m[x-1][y].accessible == true){if(m[x-1][y].boundary == false){m[x-1][y].value = m[x-1][y].value + coefficient * dv[count];} count++;}
                if(m[x+1][y].accessible == true){if(m[x+1][y].boundary == false){m[x+1][y].value = m[x+1][y].value + coefficient * dv[count];} count++;}
                if(m[x][y-1].accessible == true){if(m[x][y-1].boundary == false){m[x][y-1].value = m[x][y-1].value + coefficient * dv[count];} count++;}
                if(m[x][y+1].accessible == true){if(m[x][y+1].boundary == false){m[x][y+1].value = m[x][y+1].value + coefficient * dv[count];} count++;}
			}
			cells.clear();
			dv.clear();
		}
	}
    for(int x = no-2; x > 0; x--) {
		for(int y = mo-2; y > 0; y--) {
			old_value = m[x][y].value;
			if(m[x-1][y].accessible == true){
			cells.push_back(m[x-1][y]);
			dv.push_back(m[x][y].value - m[x-1][y].value);
			}
			if(m[x+1][y].accessible == true){
			cells.push_back(m[x+1][y]);
			dv.push_back(m[x][y].value - m[x+1][y].value);
			}
			if(m[x][y-1].accessible == true){
			cells.push_back(m[x][y-1]);
			dv.push_back(m[x][y].value - m[x][y-1].value);
			}
			if(m[x][y+1].accessible == true){
			cells.push_back(m[x][y+1]);
			dv.push_back(m[x][y].value - m[x][y+1].value);
			}
			cells.push_back(m[x][y]);
			double average = average_value(cells);
			if(m[x][y].boundary == false)m[x][y].value = average;
			DV = average - old_value;
			if(abs(DV) > change)change = abs(DV);
			total_difference = total_value(dv);
			if(total_difference == 0 || DV == 0) {
                if(m[x-1][y].accessible == true && m[x+1][y].accessible == true){
                    double xnew = (m[x-1][y].value + m[x+1][y].value) / 2.;
                    if(m[x-1][y].boundary == false){m[x-1][y].value = xnew;} if(m[x+1][y].boundary == false){m[x+1][y].value = xnew;}
                }
                if(m[x][y-1].accessible == true && m[x][y+1].accessible == true){
                    double ynew = (m[x][y-1].value + m[x][y+1].value) / 2.;
                    if(m[x][y-1].boundary == false){m[x][y-1].value = ynew;} if(m[x][y+1].boundary == false){m[x][y+1].value = ynew;}
                }
            }
			else {coefficient = -DV/total_difference;
                count = 0;
                if(m[x-1][y].accessible == true){if(m[x-1][y].boundary == false){m[x-1][y].value = m[x-1][y].value + coefficient * dv[count];} count++;}
                if(m[x+1][y].accessible == true){if(m[x+1][y].boundary == false){m[x+1][y].value = m[x+1][y].value + coefficient * dv[count];} count++;}
                if(m[x][y-1].accessible == true){if(m[x][y-1].boundary == false){m[x][y-1].value = m[x][y-1].value + coefficient * dv[count];} count++;}
                if(m[x][y+1].accessible == true){if(m[x][y+1].boundary == false){m[x][y+1].value = m[x][y+1].value + coefficient * dv[count];} count++;}
			}
			cells.clear();
			dv.clear();
		}
	}

	for(int y = 1; y < mo-1; y++){
		for(int x = 1; x < no-1; x++) {
			old_value = m[x][y].value;
			if(m[x-1][y].accessible == true){
			cells.push_back(m[x-1][y]);
			dv.push_back(m[x][y].value - m[x-1][y].value);
			}
			if(m[x+1][y].accessible == true){
			cells.push_back(m[x+1][y]);
			dv.push_back(m[x][y].value - m[x+1][y].value);
			}
			if(m[x][y-1].accessible == true){
			cells.push_back(m[x][y-1]);
			dv.push_back(m[x][y].value - m[x][y-1].value);
			}
			if(m[x][y+1].accessible == true){
			cells.push_back(m[x][y+1]);
			dv.push_back(m[x][y].value - m[x][y+1].value);
			}
			cells.push_back(m[x][y]);
			double average = average_value(cells);
			if(m[x][y].boundary == false)m[x][y].value = average;
			DV = average - old_value;
			if(abs(DV) > change)change = abs(DV);
			total_difference = total_value(dv);
			if(total_difference == 0 || DV == 0) {
                if(m[x-1][y].accessible == true && m[x+1][y].accessible == true){
                    double xnew = (m[x-1][y].value + m[x+1][y].value) / 2.;
                    if(m[x-1][y].boundary == false){m[x-1][y].value = xnew;} if(m[x+1][y].boundary == false){m[x+1][y].value = xnew;}
                }
                if(m[x][y-1].accessible == true && m[x][y+1].accessible == true){
                    double ynew = (m[x][y-1].value + m[x][y+1].value) / 2.;
                    if(m[x][y-1].boundary == false){m[x][y-1].value = ynew;} if(m[x][y+1].boundary == false){m[x][y+1].value = ynew;}
                }
            }
			else {coefficient = -DV/total_difference;
                count = 0;
                if(m[x-1][y].accessible == true){if(m[x-1][y].boundary == false){m[x-1][y].value = m[x-1][y].value + coefficient * dv[count];} count++;}
                if(m[x+1][y].accessible == true){if(m[x+1][y].boundary == false){m[x+1][y].value = m[x+1][y].value + coefficient * dv[count];} count++;}
                if(m[x][y-1].accessible == true){if(m[x][y-1].boundary == false){m[x][y-1].value = m[x][y-1].value + coefficient * dv[count];} count++;}
                if(m[x][y+1].accessible == true){if(m[x][y+1].boundary == false){m[x][y+1].value = m[x][y+1].value + coefficient * dv[count];} count++;}
			}
			cells.clear();
			dv.clear();
		}
	}

    for(int y = mo-2; y > 0; y--) {
        for(int x = no-2; x > 0; x--) {
			old_value = m[x][y].value;
			if(m[x-1][y].accessible == true){
			cells.push_back(m[x-1][y]);
			dv.push_back(m[x][y].value - m[x-1][y].value);
			}
			if(m[x+1][y].accessible == true){
			cells.push_back(m[x+1][y]);
			dv.push_back(m[x][y].value - m[x+1][y].value);
			}
			if(m[x][y-1].accessible == true){
			cells.push_back(m[x][y-1]);
			dv.push_back(m[x][y].value - m[x][y-1].value);
			}
			if(m[x][y+1].accessible == true){
			cells.push_back(m[x][y+1]);
			dv.push_back(m[x][y].value - m[x][y+1].value);
			}
			cells.push_back(m[x][y]);
			double average = average_value(cells);
			if(m[x][y].boundary == false)m[x][y].value = average;
			DV = average - old_value;
			if(abs(DV) > change)change = abs(DV);
			total_difference = total_value(dv);
			if(total_difference == 0 || DV == 0) {
                if(m[x-1][y].accessible == true && m[x+1][y].accessible == true){
                    double xnew = (m[x-1][y].value + m[x+1][y].value) / 2.;
                    if(m[x-1][y].boundary == false){m[x-1][y].value = xnew;} if(m[x+1][y].boundary == false){m[x+1][y].value = xnew;}
                }
                if(m[x][y-1].accessible == true && m[x][y+1].accessible == true){
                    double ynew = (m[x][y-1].value + m[x][y+1].value) / 2.;
                    if(m[x][y-1].boundary == false){m[x][y-1].value = ynew;} if(m[x][y+1].boundary == false){m[x][y+1].value = ynew;}
                }
            }
			else {coefficient = -DV/total_difference;
                count = 0;
                if(m[x-1][y].accessible == true){if(m[x-1][y].boundary == false){m[x-1][y].value = m[x-1][y].value + coefficient * dv[count];} count++;}
                if(m[x+1][y].accessible == true){if(m[x+1][y].boundary == false){m[x+1][y].value = m[x+1][y].value + coefficient * dv[count];} count++;}
                if(m[x][y-1].accessible == true){if(m[x][y-1].boundary == false){m[x][y-1].value = m[x][y-1].value + coefficient * dv[count];} count++;}
                if(m[x][y+1].accessible == true){if(m[x][y+1].boundary == false){m[x][y+1].value = m[x][y+1].value + coefficient * dv[count];} count++;}
			}
			cells.clear();
			dv.clear();
		}
	}


	Iteration next;
	next.it = m;
	next.error = change;
	return next;
}

void Asymmetric_Finite_Volume::solve() {
	matrix first = grid.get_values();
	double err = 1000;
	unsigned int k = 1;
	Iteration o;
	Iteration n;
	o.it = first;
	o.error = err;
	while(err > precision && k < maxit) {
		n = iteration(o);
		err = n.error;
		o = n;
		k++;
	}
	solution.set_values(n.it);
	solution.set_coordinates(grid.get_coordinates());
	solution.set_gradients(grid.get_gradients());
	its = k;
}

Grid Asymmetric_Finite_Volume::get_solution() {
	Asymmetric_Finite_Volume::solve();
	return solution;
}
