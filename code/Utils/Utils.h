#ifndef UTILS_H_
#define UTILS_H_

#include "../Structures/Grid.h"

using namespace std;

inline double average_value(vector<Value> vec) {
	double total = 0;
	for (int i = 0; i < vec.size(); i++) {
		total += vec[i].value;
	}
	return total / vec.size();
}

inline double total_value(vector<Value> vec) {
	double total = 0;
	for (int i = 0; i < vec.size(); i++) {
		total += vec[i].value;
	}
	return total;
}

inline double total_value(vector<double> vec) {
	double total = 0;
	for (int i = 0; i < vec.size(); i++) {
		total += vec[i];
	}
	return total;
}

inline double average_value(vector<double> vec) {
	double total = 0;
	for (int i = 0; i < vec.size(); i++) {
		total += vec[i];
	}
	return total / vec.size();
}

inline double average_grid(Grid entry){
  matrix mat = entry.get_values();
  double total = 0;
  for (int i = 0; i< mat.size(); i++){
    for (int j = 0; j< mat[0].size(); j++){
      total += mat[i][j].value;
    }
  }
  return total / (mat.size()*mat[0].size());
}

inline double sum_grid(Grid entry) {
	matrix mat = entry.get_values();
	double total = 0;
	for (int i = 0; i< mat.size(); i++){
		for (int j = 0; j< mat[0].size(); j++){
			total += mat[i][j].value;
		}
	}
	return total;
}



#endif /* UTILS_H_ */
