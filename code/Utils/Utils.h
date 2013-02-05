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

#endif /* UTILS_H_ */
