/*
 * Coordinate.h
 *
 *  Created on: 2 Feb 2013
 *      Author: david
 */

#ifndef COORDINATE_H_
#define COORDINATE_H_

class Coordinate {
private:
	double xcoor;
	double ycoor;
public:
	void set_x(double i) {
		xcoor = i;
	}
	void set_y(double j) {
		ycoor = j;
	}
	void set_xy(double i, double j) {
		xcoor = i;
		ycoor = j;
	}
	double get_x() {
		return xcoor;
	}
	double get_y() {
		return ycoor;
	}

	double distance(Coordinate two) {
		return sqrt(
				(xcoor - two.get_x()) * (xcoor - two.get_x())
				+ (ycoor - two.get_y()) * (ycoor - two.get_y()));
	}
};


#endif /* COORDINATE_H_ */
