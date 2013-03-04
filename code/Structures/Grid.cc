#include "Grid.h"

using namespace std;

//Silly round function so that I can control exactly how it works

int Grid::round_own(double a) {
	return int(a + 0.5);
}

Grid::Grid() :
			Grid::Grid(50, 50) {
}

Grid::Grid(unsigned int x, unsigned int y) {
	unsigned int ix = x + 1;
	unsigned int iy = y + 1;
	vector<Value> dummy_vec_val;
	Value dummy_val;
	dummy_val.value = 0;
	dummy_val.boundary = false;
	dummy_val.accessible = true;
	dummy_val.flag = 0;
	while (iy > 0) {
		dummy_vec_val.push_back(dummy_val);
		iy--;
	}
	while (ix > 0) {
		values.push_back(dummy_vec_val);
		ix--;
	}
	Coordinate coordinate;
	vector<Coordinate> dummy_vec_coord;
	while (ix <= x) {
		for (int z = 0; z <= y; z++) {
			coordinate.set_x((double) ix);
			coordinate.set_y(z);
			dummy_vec_coord.push_back(coordinate);
		}
		points.push_back(dummy_vec_coord);
		dummy_vec_coord.clear();
		ix++;
	}
	Grad dummy_grad;
	vector<Grad> dummy_vec_grad;
	dummy_grad.dx = 0;
	dummy_grad.dy = 0;
	ix = x + 1;
	iy = y + 1;
	while (iy > 0) {
		dummy_vec_grad.push_back(dummy_grad);
		iy--;
	}
	while (ix > 0) {
		gradients.push_back(dummy_vec_grad);
		ix--;
	}
}

Grid::~Grid() {
}

//Set range (so that it's possible to use a different increment than 1). Not really used at the moment

void Grid::set_range(double x, double y) {
	unsigned int x_size = points.size() - 1;
	unsigned int y_size = points[0].size() - 1;
	double x_mult = x / x_size;
	double y_mult = y / y_size;
	for (int it1 = 0; it1 < x_size + 1; it1++) {
		for (int it2 = 0; it2 < y_size + 1; it2++) {
			double x_val = points[it1][it2].get_x();
			double y_val = points[it1][it2].get_y();
			if (x_val != 0)
				points[it1][it2].set_x(x_val * x_mult);
			if (y_val != 0)
				points[it1][it2].set_y(y_val * y_mult);
		}
	}
}

//Set value of individual cell without making it a boundary point

void Grid::set_value(unsigned int x, unsigned int y, double val) {
	assert(x < values.size() && y < values[0].size() && "Outside of range");
	values[x][y].value = val;
}

//Make a cell a boundary point without changing its value

void Grid::set_boundary_point(unsigned int x, unsigned int y, bool bound) {
	assert(x < values.size() && y < values[0].size() && "Outside of range");
	values[x][y].boundary = bound;
}

//Set both value and make boundary point (most commonly used I imagine)

void Grid::set_boundary_value(unsigned int x, unsigned int y, double val) {
	assert(x < values.size() && y < values[0].size() && "Outside of range");
	values[x][y].boundary = true;
	values[x][y].value = val;
}

//Same as above but accepts doubles (so if you for some reason want to define
//a boundary shape in your own code you won't have to round floats all the time)

void Grid::set_boundary_value_float(double xd, double yd, double val) {
	unsigned int x = round_own(abs(xd));
	unsigned int y = round_own(abs(yd));
	assert(x < values.size() && y < values[0].size() && "Outside of range");
	values[x][y].boundary = true;
	values[x][y].value = val;
}

void Grid::set_flow(double left, double right) {
	double gradient = (right - left) / (values.size() - 1);
	for (int y = 0; y < values[0].size(); y++) {
		values[0][y].value = left;
		values[0][y].boundary = true;
		values[values.size() - 1][y].value = right;
		values[values.size() - 1][y].boundary = true;
	}
	for (int x = 0; x < values.size(); x++) {
		values[x][0].value = left + x * gradient;
		values[x][0].boundary = true;
		values[x][values[0].size() - 1].value = left + x * gradient;
		values[x][values[0].size() - 1].boundary = true;
	}
	for (int y = 1; y < values[0].size() - 1; y++) {
		for (int x = 1; x < values.size() - 1; x++) {
			values[x][y].value = left + x * gradient;
		}
	}
}

coordinate_matrix Grid::get_coordinates() {
	return points;
}
matrix Grid::get_values() {
	return values;
}
grad_matrix Grid::get_gradients() {
	return gradients;
}

void Grid::set_coordinates(coordinate_matrix coords) {
	points = coords;
}
void Grid::set_values(matrix vals) {
	values = vals;
}
void Grid::set_gradients(grad_matrix grads) {
	gradients = grads;
}

//finds -ve gradient of each point in x and y direction. Equivalent to E_x and E_y. assumes increment =1.
void Grid::efield() {
	double dx1, dy1;
	for (int x = 0; x < gradients.size() - 1; x++) {
		for (int y = 0; y < gradients.size() - 1; y++) {

			dx1 = values[x][y].value - values[x + 1][y].value;
			dy1 = values[x][y].value - values[x][y + 1].value;
			gradients[x][y].e_size = sqrt(dx1 * dx1 + dy1 * dy1);
			gradients[x][y].dx = dx1 / gradients[x][y].e_size;
			gradients[x][y].dy = dy1 / gradients[x][y].e_size;
		}
	}
}

// small function that compares two Value type variables (.value and .flag). returns 1 if they are equal

bool Grid::compare(Value nn, Value mm) {
	if (nn.value == mm.value && nn.flag == mm.flag) {
		return 1;
	} else
		return 0;
}

// calculates equip.lines. n - number of eq.lines you need. xmax, ymax, Emax - obvious. line_width: for ex, if line-width
// is set to 2, it means it will have width of 2 points. ( if line_width = 1 and grid is 50x50, the lines will be very wide,
// on the contrary, if line_width = 1 and grid 500x500 , they will be 10 times narrower). menu:
// 1 - a point is equal to 2 if it is on equipotential, equal to 1 if it is on the object
// 2 - prints out only eq.lines with values of 1
// 3 - plots eq.lines with different values, and an object of 2*Emax value
// 4 - plots only eq.lines with different values

void Grid::equip_values(int n, int xmax, int ymax, double Emax, int line_width,
		int menu) {

	double dx = (double) xmax / (n - 1);

	for (double ii = 0; ii <= xmax; ii = ii + dx) {
		int i = round_own(ii);
		int xi = i;
		int yi = 0;
		Value prev_prev;
		prev_prev.value = 999.999;
		prev_prev.flag = 1;
		Value prev;
		prev.value = 999.998;
		prev.flag = 1;
		Value current = values[xi][yi];
		double eq_val = values[xi][yi].value;
		double diff_left = 100;
		if (xi != 0) {
			diff_left = abs(values[xi - 1][yi].value - eq_val);
		}
		double diff_right = 100;
		if (xi != xmax) {
			diff_right = abs(values[xi + 1][yi].value - eq_val);
		}
		double diff_up = abs(values[xi][yi + 1].value - eq_val);
		values[xi][yi].flag = 1;

		if (diff_up <= diff_right && diff_up <= diff_left) {
			check_and_mark_cells(xi, yi, 0, 1, prev_prev, prev, current);
		} else if (diff_right <= diff_left) {
			check_and_mark_cells(xi, yi, 1, 0, prev_prev, prev, current);
		} else {
			check_and_mark_cells(xi, yi, -1, 0, prev_prev, prev, current);
		}

		for (;;) {

			if (xi == xmax
					|| (compare(prev, values[xi + 1][yi])
							|| (compare(prev, values[xi][yi - 1])
									&& compare(prev_prev,
											values[xi + 1][yi - 1])))) {
				diff_left = abs(values[xi - 1][yi].value - eq_val);
				diff_up = abs(values[xi][yi + 1].value - eq_val);
				if (diff_up <= diff_left) {
					check_and_mark_cells(xi, yi, 0, 1, prev_prev, prev,
							current);
				} else {
					check_and_mark_cells(xi, yi, -1, 0, prev_prev, prev,
							current);
				}
			}

			else if (xi == 0
					|| (compare(prev, values[xi - 1][yi])
							|| (compare(prev, values[xi][yi - 1])
									&& compare(prev_prev,
											values[xi - 1][yi - 1])))) {
				diff_right = abs(values[xi + 1][yi].value - eq_val);
				diff_up = abs(values[xi][yi + 1].value - eq_val);
				if (diff_up <= diff_right) {
					check_and_mark_cells(xi, yi, 0, 1, prev_prev, prev,
							current);
				} else {
					check_and_mark_cells(xi, yi, 1, 0, prev_prev, prev,
							current);
				}
			} else {
				diff_left = abs(values[xi - 1][yi].value - eq_val);
				diff_right = abs(values[xi + 1][yi].value - eq_val);
				diff_up = abs(values[xi][yi + 1].value - eq_val);

				if ((diff_up <= diff_right) && (diff_up <= diff_left)) {
					check_and_mark_cells(xi, yi, 0, 1, prev_prev, prev,
							current);
				} else if (diff_right <= diff_left) {
					check_and_mark_cells(xi, yi, 1, 0, prev_prev, prev,
							current);
				} else {
					check_and_mark_cells(xi, yi, -1, 0, prev_prev, prev,
							current);
				}
			}

			if (yi >= ymax || xi < 0 || xi > xmax) {
				break;
			}

			// extra code for case if the eq. line goes through the figure

			if (xi != 0 && xi != xmax && yi != 0 && yi != ymax
					&& values[xi][yi].boundary == 1) {
				int i = round_own(ii);
				int xi = i;
				int yi = ymax;
				Value prev_prev;
				prev_prev.value = 999.999;
				prev_prev.flag = 1;
				Value prev;
				prev.value = 999.998;
				prev.flag = 1;
				Value current = values[xi][yi];
				double eq_val = values[xi][yi].value;
				double diff_left = 100;
				if (xi != 0) {
					abs(values[xi + 1][yi].value - eq_val);
				}
				double diff_right = 100;
				if (xi != xmax) {
					abs(values[xi - 1][yi].value - eq_val);
				}
				double diff_up = abs(values[xi][yi - 1].value - eq_val);
				values[xi][yi].flag = 1;

				if (diff_up <= diff_right && diff_up <= diff_left) {
					check_and_mark_cells(xi, yi, 0, -1, prev_prev, prev,
							current);
				} else if (diff_right <= diff_left) {
					check_and_mark_cells(xi, yi, -1, 0, prev_prev, prev,
							current);
				} else {
					check_and_mark_cells(xi, yi, +1, 0, prev_prev, prev,
							current);
				}

				for (;;) {

					if (xi == 0
							|| (compare(prev, values[xi - 1][yi])
									|| (compare(prev, values[xi][yi + 1])
											&& compare(prev_prev,
													values[xi - 1][yi + 1])))) {
						diff_left = abs(values[xi + 1][yi].value - eq_val);
						diff_up = abs(values[xi][yi - 1].value - eq_val);
						if (diff_up <= diff_left) {
							check_and_mark_cells(xi, yi, 0, -1, prev_prev, prev,
									current);
						}

						else {
							check_and_mark_cells(xi, yi, +1, 0, prev_prev, prev,
									current);
						}
					}

					else if (xi == xmax
							|| (compare(prev, values[xi + 1][yi])
									|| (compare(prev, values[xi][yi + 1])
											&& compare(prev_prev,
													values[xi + 1][yi + 1])))) {
						diff_right = abs(values[xi - 1][yi].value - eq_val);
						diff_up = abs(values[xi][yi - 1].value - eq_val);
						if (diff_up <= diff_right) {
							check_and_mark_cells(xi, yi, 0, -1, prev_prev, prev,
									current);
						}

						else {
							check_and_mark_cells(xi, yi, -1, 0, prev_prev, prev,
									current);
						}
					} else {
						diff_left = abs(values[xi + 1][yi].value - eq_val);
						diff_right = abs(values[xi - 1][yi].value - eq_val);
						diff_up = abs(values[xi][yi - 1].value - eq_val);

						if ((diff_up <= diff_right) && (diff_up <= diff_left)) {
							check_and_mark_cells(xi, yi, 0, -1, prev_prev, prev,
									current);
						}

						else if (diff_right <= diff_left) {
							check_and_mark_cells(xi, yi, -1, 0, prev_prev, prev,
									current);
						} else {
							check_and_mark_cells(xi, yi, +1, 0, prev_prev, prev,
									current);
						}
					}
					if (xi != 0 && xi != xmax && yi != 0 && yi != ymax
							&& values[xi][yi].boundary == 1) {
						break;
					} else if (yi <= 0 || xi < 0 || xi > xmax) {
						break;
					}
				}

				break;
			}
		}
	}

	// Makes the line wider if line_width is set to be 2 or higher.

	if (line_width >= 2) {
		for (int xs = 0; xs < values.size(); xs++) {
			for (int ys = 0; ys < values[0].size(); ys++) {
				if (values[xs][ys].flag == 1) {
					int iii = 1;
					int kkk = 1;
					for (int i = 1; i <= line_width - 1; ++i) {
						if (iii % 2 == 1 || xs == 0) {
							if (xs + kkk <= xmax) {
								values[xs + kkk][ys].flag = 2;
							}
						} else if (iii % 2 == 0 || xs == xmax) {
							if (xs - kkk >= 0) {
								values[xs - kkk][ys].flag = 2;
								++kkk;
							}
						}
						++iii;
					}
				}
			}
		}
	}

	// This part of the code outputs the values for each point depending on value of "menu" set by user

	if (menu == 1) {

		for (int xs = 0; xs < values.size(); xs++) {
			for (int ys = 0; ys < values[0].size(); ys++) {
				if (values[xs][ys].boundary == 1) {
					values[xs][ys].value = 1;
				} else if ((values[xs][ys].flag == 1 || values[xs][ys].flag == 2)) {
					values[xs][ys].value = 2;
				} else {
					values[xs][ys].value = 0;
				}
				if ((xs == 0 || ys == 0 || xs == values.size() - 1
						|| ys == values[0].size() - 1)
						&& (values[xs][ys].flag == 0)) {
					values[xs][ys].value = 0;
				} else if ((xs == 0 || ys == 0 || xs == values.size() - 1
						|| ys == values[0].size() - 1)
						&& (values[xs][ys].flag == 1 || values[xs][ys].flag == 2)) {
					values[xs][ys].value = 2;
				}
			}
		}
	}

	else if (menu == 2) {

		for (int xs = 0; xs < values.size(); xs++) {
			for (int ys = 0; ys < values[0].size(); ys++) {
				if (values[xs][ys].boundary == 1) {
					values[xs][ys].value = 1;
				} else if ((values[xs][ys].flag == 1 || values[xs][ys].flag == 2)) {
					values[xs][ys].value = 1;
				} else {
					values[xs][ys].value = 0;
				}
				if ((xs == 0 || ys == 0 || xs == values.size() - 1
						|| ys == values[0].size() - 1)
						&& (values[xs][ys].flag == 0)) {
					values[xs][ys].value = 0;
				} else if ((xs == 0 || ys == 0 || xs == values.size() - 1
						|| ys == values[0].size() - 1)
						&& (values[xs][ys].flag == 1 || values[xs][ys].flag == 2)) {
					values[xs][ys].value = 1;
				}
			}
		}
	}

	else if (menu == 3) {

		for (int xs = 0; xs < values.size(); xs++) {
			for (int ys = 0; ys < values[0].size(); ys++) {
				if (xs != 0 && ys != 0 && xs != values.size() - 1
						&& ys != values[0].size() - 1
						&& values[xs][ys].boundary == 1) {
					values[xs][ys].value = 2 * Emax;
				} else if ((values[xs][ys].flag != 1 && values[xs][ys].flag != 2)) {
					values[xs][ys].value = (-2) * Emax;
				}
				if ((xs == 0 || ys == 0 || xs == values.size() - 1
						|| ys == values[0].size() - 1)
						&& (values[xs][ys].flag == 0)) {
					values[xs][ys].value = (-2) * Emax;
				}
			}
		}
	}

	else if (menu == 4) {

		for (int xs = 0; xs < values.size(); xs++) {
			for (int ys = 0; ys < values[0].size(); ys++) {
				if ((values[xs][ys].flag != 1 && values[xs][ys].flag != 2)
						&& ((xs != 0 && ys != 0 && xs != values.size() - 1
								&& ys != values[0].size() - 1)
								&& (values[xs][ys].boundary != 1))) {
					values[xs][ys].value = (-2) * Emax;
				}
				if ((xs == 0 || ys == 0 || xs == values.size() - 1
						|| ys == values[0].size() - 1)
						&& (values[xs][ys].flag == 0)) {
					values[xs][ys].value = (-2) * Emax;
				}
			}
		}
	}

}

void Grid::check_and_mark_cells(int &xa, int &ya, int deltax, int deltay,
		Value &prev_prev2, Value &prev2, Value &current2) {
	xa = xa + deltax;
	ya = ya + deltay;
	values[xa][ya].flag = 1;
	prev_prev2 = prev2;
	prev2 = current2;
	current2 = values[xa][ya];
}

//////
//////
//////

// BOUNDARY CONDITION FUNCTIONS SHOULD BE WRITTEN BELOW

//////
//////
//////

//Think of this as a simple way to create a uniform electric field (or liquid flow)
//from left to right or the other way around

//Create an inaccessible circle

void Grid::set_circle_noflow(int x, int y, unsigned int r, double val) {
	if (x - r < 0 || x + r > values.size() - 1 || y - r < 0
			|| y + r > values[0].size() - 1)
		cout << "Out of range." << endl;
	else {
		for (int xs = x - r; xs <= x + r; xs++) {
			for (int ys = y - r; ys <= y + r; ys++) {
				Coordinate xy;
				xy.set_xy(xs, ys);
				Coordinate mid;
				mid.set_xy(x, y);
				if (mid.distance(xy) < r) {
					values[xs][ys].value = val;
					values[xs][ys].accessible = false;
				}
			}
		}
	}
}

void Grid::set_boundary_shape(int x1, int y1, int r, int z, double val,
		Shape shape) {
	set_boundary_shape(x1,y1,r,z,val,shape,0,0,0,0,0,0);
}

void Grid::set_boundary_shape(int x1, int y1, int r, int z, double val,
		Shape shape, int x2, int x3, int x4, int y2, int y3, int y4) {

	switch (shape) {

	///CIRCLE
	case circle: {
		if (x1 - r < 0 || x1 + r > values.size() - 1 || y1 - r < 0
				|| y1 + r > values[0].size() - 1)
			cout << "Out of range." << endl;
		else {
			for (int xs = x1 - r; xs <= x1 + r; xs++) {
				for (int ys = y1 - r; ys <= y1 + r; ys++) {
					Coordinate xy;
					xy.set_xy(xs, ys);
					Coordinate mid;
					mid.set_xy(x1, y1);
					if (mid.distance(xy) < r) {
						values[xs][ys].value = val;
						values[xs][ys].boundary = true;
					}
				}
			}
		}
		break;
	}

	//SEMICIRCLES
	case semicircle_north: {
		if (x1 - r < 0 || x1 + r > values.size() - 1 || y1 < 0
				|| y1 + r > values[0].size() - 1)
			cout << "Out of range." << endl;
		else {
			for (int xs = x1 - r; xs <= x1 + r; xs++) {
				for (int ys = y1; ys <= y1 + r; ys++) {
					Coordinate xy;
					xy.set_xy(xs, ys);
					Coordinate mid;
					mid.set_xy(x1, y1);
					if (mid.distance(xy) < r) {
						values[xs][ys].value = val;
						values[xs][ys].boundary = true;
					}
				}
			}
		}
		break;
	}

	case semicircle_south: {
		if (x1 - r < 0 || x1 + r > values.size() - 1 || y1 - r < 0
				|| y1 > values[0].size() - 1)
			cout << "Out of range." << endl;
		else {
			for (int xs = x1 - r; xs <= x1 + r; xs++) {
				for (int ys = y1 - r; ys <= y1; ys++) {
					Coordinate xy;
					xy.set_xy(xs, ys);
					Coordinate mid;
					mid.set_xy(x1, y1);
					if (mid.distance(xy) < r) {
						values[xs][ys].value = val;
						values[xs][ys].boundary = true;
					}
				}
			}
		}
		break;
	}

	case semicircle_east: {
		if (x1 < 0 || x1 + r > values.size() - 1 || y1 - r < 0
				|| y1 > values[0].size() - 1)
			cout << "Out of range." << endl;
		else {
			for (int xs = x1; xs <= x1 + r; xs++) {
				for (int ys = y1 - r; ys <= y1 + r; ys++) {
					Coordinate xy;
					xy.set_xy(xs, ys);
					Coordinate mid;
					mid.set_xy(x1, y1);
					if (mid.distance(xy) < r) {
						values[xs][ys].value = val;
						values[xs][ys].boundary = true;
					}
				}
			}
		}
		break;
	}

	case semicircle_west: {
		if (x1 - r < 0 || x1 > values.size() - 1 || y1 - r < 0
				|| y1 > values[0].size() - 1)
			cout << "Out of range." << endl;
		else {
			for (int xs = x1 - r; xs <= x1; xs++) {
				for (int ys = y1 - r; ys <= y1 + r; ys++) {
					Coordinate xy;
					xy.set_xy(xs, ys);
					Coordinate mid;
					mid.set_xy(x1, y1);
					if (mid.distance(xy) < r) {
						values[xs][ys].value = val;
						values[xs][ys].boundary = true;
					}
				}
			}
		}
		break;
	}

	///RECTANGLE
	case rectangle: {
		x2 = y1;
		y1 = r;
		y2 = z;
		if (x1 > values.size() - 1 || x2 > values.size() - 1
				|| y1 > values.size() - 1 || y2 > values.size() - 1)
			cout << "Out of range." << endl;
		else {
			for (int xs = min(x1, x2); xs <= max(x1, x2); xs++) {
				for (int ys = min(y1, y2); ys <= max(y1, y2); ys++) {
					values[xs][ys].value = val;
					values[xs][ys].boundary = true;
				}
			}
		}
		break;
	}

	///TRIANGLE
	case triangle: {
		x2 = y1;
		int y_base = r;
		int y_tip = z;
		if (x1 > values.size() - 1 || x2 > values.size() - 1
				|| y_base > values.size() - 1 || y_tip > values.size() - 1)
			cout << "Out of range." << endl;
		else {
			double slope = (double) (y_tip - y_base) / (0.5 * abs(x1 - x2));
			int xc = (x1 + x2) / 2;
			for (int xs = min(x1, x2); xs <= max(x1, x2); xs++) {
				for (int ys = min(y_tip, y_base); ys <= max(y_tip, y_base);
						ys++) {
					if (y_tip > y_base && ys <= y_tip + slope * (xs - xc)
							&& ys <= y_tip - slope * (xs - xc)) {
						values[xs][ys].value = val;
						values[xs][ys].boundary = true;
					}
					if (y_tip < y_base && ys >= y_tip + slope * (xs - xc)
							&& ys >= y_tip - slope * (xs - xc)) {
						values[xs][ys].value = val;
						values[xs][ys].boundary = true;
					}
				}
			}
		}
		break;
	}

	///ELLIPSE
	case ellipse: {
		int rx = r;
		int ry = z;
		if (x1 - rx < 0 || y1 - ry < 0 || x1 + rx > values.size() - 1
				|| y1 + ry > values.size() - 1)
			cout << "Out of range." << endl;
		for (int xs = x1 - rx; xs <= x1 + rx; xs++) {
			for (int ys = y1 - ry; ys <= y1 + ry; ys++) {
				if (pow(((double) (xs - x1) / rx), 2)
						+ pow(((double) (ys - y1) / ry), 2) <= 1) {
					values[xs][ys].value = val;
					values[xs][ys].boundary = true;
				}
			}
		}
		break;
	}

	case star: {
		if (x1 > values.size() - 1 || x4 > values.size() - 1 || y1 > values.size() - 1 || y4 > values.size() - 1)
			cout << "Out of range." << endl;
		else {
			for (int xs=x2; xs <= x3; xs++) {
				for (int ys=y2; ys <= y3; ys++) {
					values[xs][ys].value=val;
					values[xs][ys].boundary=true;
				}
			}

			double slope=(double) (y4 - y3)/ (0.5*(x3 - x2));
			double xc=(x2+x3)/2;
			for (int xs=x2; xs <= x3; xs++) {
				for (int ys=y3; ys <= y4; ys++) {
					if ( ys <= y4 + slope * (xs - xc) && ys <= y4 - slope * (xs - xc)) {
						values[xs][ys].value = val;
						values[xs][ys].boundary = true;
					}
				}
			}

			for (int xs=x2; xs <= x3; xs++) {
				for (int ys=y1; ys <= y2; ys++) {
					if ( ys >= y1 + slope * (xs - xc) && ys >= y1 - slope * (xs - xc)) {
						values[xs][ys].value = val;
						values[xs][ys].boundary = true;
					}
				}
			}

			slope=(double) (x4 - x3)/ (0.5*(y3 - y2));
			double yc=(y2+y3)/2;
			for (int ys=y2; ys <= y3; ys++) {
				for (int xs=x3; xs <= x4; xs++) {
					if ( xs <= x4 + slope * (ys - yc) && xs <= x4 - slope * (ys - yc)) {
						values[xs][ys].value = val;
						values[xs][ys].boundary = true;
					}
				}
			}

			for (int ys=y2; ys <= y3; ys++) {
				for (int xs=x1; xs <= x2; xs++) {
					if ( xs >= x1 + slope * (ys - yc) && xs >= x1 - slope * (ys - yc)) {
						values[xs][ys].value = val;
						values[xs][ys].boundary = true;
					}
				}
			}
		}
		break;
	}
	case random_shape: {
		srand(time(0));
		int rand_shape = rand() % 9;
		Shape new_shape;
		switch (rand_shape) {
		case 0:
			new_shape = circle;
			break;
		case 1:
			new_shape = semicircle_north;
			break;
		case 2:
			new_shape = semicircle_south;
			break;
		case 3:
			new_shape = semicircle_west;
			break;
		case 4:
			new_shape = semicircle_east;
			break;
		case 5:
			new_shape = rectangle;
			break;
		case 6:
			new_shape = triangle;
			break;
		case 7:
			new_shape = ellipse;
			break;
		case 8:
			new_shape = star;
			break;
		}
		int x1 = 1 + rand()%(values.size() - 3);
		int x2 = 1 + rand()%(values.size() - 3);
		int x3 = 1 + rand()%(values.size() - 3);
		int x4 = 1 + rand()%(values.size() - 3);
		int x5 = (1 + rand()%(values.size() - 3) + 1 + rand()%(values[0].size() - 3)) / 4;

		int y1 = 1 + rand()%(values[0].size() - 3);
		int y2 = 1 + rand()%(values[0].size() - 3);
		int y3 = 1 + rand()%(values[0].size() - 3);
		int y4 = 1 + rand()%(values[0].size() - 3);
		int y5 = (1 + rand()%(values.size() - 3) + 1 + rand()%(values[0].size() - 3)) / 4;

		set_boundary_shape(x1,y1,x5,y5, val, new_shape,x2,x3,x4,y2,y3,y4);
	}

	} ///end of switch
}

void Grid::set_boundary_shape(int x, int y, int r, int z,
		Shape shape) {
	set_boundary_shape(x,y,r,z,shape,0,0,0,0,0,0);
}

void Grid::set_boundary_shape(int x, int y, int r, int z,
		Shape shape,  int x2, int x3, int x4, int y2, int y3, int y4) {

	switch (shape) {

	///CIRCLE
	case circle: {
		if (x - r < 0 || x + r > values.size() - 1 || y - r < 0
				|| y + r > values[0].size() - 1)
			cout << "Out of range." << endl;
		else {
			for (int xs = x - r; xs <= x + r; xs++) {
				for (int ys = y - r; ys <= y + r; ys++) {
					Coordinate xy;
					xy.set_xy(xs, ys);
					Coordinate mid;
					mid.set_xy(x, y);
					if (mid.distance(xy) < r) {
						values[xs][ys].boundary = true;
						values[xs][ys].flag = 1;
					}
				}
			}
		}
		break;
	}

	//SEMICIRCLES
	case semicircle_north: {
		if (x - r < 0 || x + r > values.size() - 1 || y < 0
				|| y + r > values[0].size() - 1)
			cout << "Out of range." << endl;
		else {
			for (int xs = x - r; xs <= x + r; xs++) {
				for (int ys = y; ys <= y + r; ys++) {
					Coordinate xy;
					xy.set_xy(xs, ys);
					Coordinate mid;
					mid.set_xy(x, y);
					if (mid.distance(xy) < r) {
						values[xs][ys].boundary = true;
						values[xs][ys].flag = 1;
					}
				}
			}
		}
		break;
	}

	case semicircle_south: {
		if (x - r < 0 || x + r > values.size() - 1 || y - r < 0
				|| y > values[0].size() - 1)
			cout << "Out of range." << endl;
		else {
			for (int xs = x - r; xs <= x + r; xs++) {
				for (int ys = y - r; ys <= y; ys++) {
					Coordinate xy;
					xy.set_xy(xs, ys);
					Coordinate mid;
					mid.set_xy(x, y);
					if (mid.distance(xy) < r) {
						values[xs][ys].boundary = true;
						values[xs][ys].flag = 1;
					}
				}
			}
		}
		break;
	}

	case semicircle_east: {
		if (x < 0 || x + r > values.size() - 1 || y - r < 0
				|| y > values[0].size() - 1)
			cout << "Out of range." << endl;
		else {
			for (int xs = x; xs <= x + r; xs++) {
				for (int ys = y - r; ys <= y + r; ys++) {
					Coordinate xy;
					xy.set_xy(xs, ys);
					Coordinate mid;
					mid.set_xy(x, y);
					if (mid.distance(xy) < r) {
						values[xs][ys].boundary = true;
						values[xs][ys].flag = 1;
					}
				}
			}
		}
		break;
	}

	case semicircle_west: {
		if (x - r < 0 || x > values.size() - 1 || y - r < 0
				|| y > values[0].size() - 1)
			cout << "Out of range." << endl;
		else {
			for (int xs = x - r; xs <= x; xs++) {
				for (int ys = y - r; ys <= y + r; ys++) {
					Coordinate xy;
					xy.set_xy(xs, ys);
					Coordinate mid;
					mid.set_xy(x, y);
					if (mid.distance(xy) < r) {
						values[xs][ys].boundary = true;
						values[xs][ys].flag = 1;
					}
				}
			}
		}
		break;
	}

	///RECTANGLE
	case rectangle: {
		int x1 = x;
		int x2 = y;
		int y1 = r;
		int y2 = z;
		if (x1 > values.size() - 1 || x2 > values.size() - 1
				|| y1 > values.size() - 1 || y2 > values.size() - 1)
			cout << "Out of range." << endl;
		else {
			for (int xs = min(x1, x2); xs <= max(x1, x2); xs++) {
				for (int ys = min(y1, y2); ys <= max(y1, y2); ys++) {
					values[xs][ys].boundary = true;
					values[xs][ys].flag = 1;
				}
			}
		}
		break;
	}

	///TRIANGLE
	case triangle: {
		int x1 = x;
		int x2 = y;
		int y_base = r;
		int y_tip = z;
		if (x1 > values.size() - 1 || x2 > values.size() - 1
				|| y_base > values.size() - 1 || y_tip > values.size() - 1)
			cout << "Out of range." << endl;
		else {
			double slope = (double) (y_tip - y_base) / (0.5 * abs(x1 - x2));
			int xc = (x1 + x2) / 2;
			for (int xs = min(x1, x2); xs <= max(x1, x2); xs++) {
				for (int ys = min(y_tip, y_base); ys <= max(y_tip, y_base);
						ys++) {
					if (y_tip > y_base && ys <= y_tip + slope * (xs - xc)
							&& ys <= y_tip - slope * (xs - xc)) {
						values[xs][ys].boundary = true;
						values[xs][ys].flag = 1;
					}
					if (y_tip < y_base && ys >= y_tip + slope * (xs - xc)
							&& ys >= y_tip - slope * (xs - xc)) {
						values[xs][ys].boundary = true;
						values[xs][ys].flag = 1;
					}
				}
			}
		}
		break;
	}

	///ELLIPSE
	case ellipse: {
		int rx = r;
		int ry = z;
		if (x - rx < 0 || y - ry < 0 || x + rx > values.size() - 1
				|| y + ry > values.size() - 1)
			cout << "Out of range." << endl;
		for (int xs = x - rx; xs <= x + rx; xs++) {
			for (int ys = y - ry; ys <= y + ry; ys++) {
				if (pow(((double) (xs - x) / rx), 2)
						+ pow(((double) (ys - y) / ry), 2) <= 1) {
					values[xs][ys].boundary = true;
					values[xs][ys].flag = 1;
				}
			}
		}
		break;
	}
	case star: {
		int x1 = x;
		int y1 = y;
		if (x1 > values.size() - 1 || x4 > values.size() - 1 || y1 > values.size() - 1 || y4 > values.size() - 1)
			cout << "Out of range." << endl;
		else {
			for (int xs=x2; xs <= x3; xs++) {
				for (int ys=y2; ys <= y3; ys++) {
					values[xs][ys].flag=1;
					values[xs][ys].boundary=true;
				}
			}

			double slope=(double) (y4 - y3)/ (0.5*(x3 - x2));
			double xc=(x2+x3)/2;
			for (int xs=x2; xs <= x3; xs++) {
				for (int ys=y3; ys <= y4; ys++) {
					if ( ys <= y4 + slope * (xs - xc) && ys <= y4 - slope * (xs - xc)) {
						values[xs][ys].flag=1;
						values[xs][ys].boundary = true;
					}
				}
			}

			for (int xs=x2; xs <= x3; xs++) {
				for (int ys=y1; ys <= y2; ys++) {
					if ( ys >= y1 + slope * (xs - xc) && ys >= y1 - slope * (xs - xc)) {
						values[xs][ys].flag=1;
						values[xs][ys].boundary = true;
					}
				}
			}

			slope=(double) (x4 - x3)/ (0.5*(y3 - y2));
			double yc=(y2+y3)/2;
			for (int ys=y2; ys <= y3; ys++) {
				for (int xs=x3; xs <= x4; xs++) {
					if ( xs <= x4 + slope * (ys - yc) && xs <= x4 - slope * (ys - yc)) {
						values[xs][ys].flag=1;
						values[xs][ys].boundary = true;
					}
				}
			}

			for (int ys=y2; ys <= y3; ys++) {
				for (int xs=x1; xs <= x2; xs++) {
					if ( xs >= x1 + slope * (ys - yc) && xs >= x1 - slope * (ys - yc)) {
						values[xs][ys].flag=1;
						values[xs][ys].boundary = true;
					}
				}
			}
		}
		break;
	}
	case random_shape: {
		srand(time(0));
		int rand_shape = rand() % 9;
		Shape new_shape;
		switch (rand_shape) {
		case 0:
			new_shape = circle;
			break;
		case 1:
			new_shape = semicircle_north;
			break;
		case 2:
			new_shape = semicircle_south;
			break;
		case 3:
			new_shape = semicircle_west;
			break;
		case 4:
			new_shape = semicircle_east;
			break;
		case 5:
			new_shape = rectangle;
			break;
		case 6:
			new_shape = triangle;
			break;
		case 7:
			new_shape = ellipse;
			break;
		case 8:
			new_shape = star;
			break;
		}
		int x1 = 1 + rand()%(values.size() - 3);
		int x2 = 1 + rand()%(values.size() - 3);
		int x3 = 1 + rand()%(values.size() - 3);
		int x4 = 1 + rand()%(values.size() - 3);
		int x5 = (1 + rand()%(values.size() - 3) + 1 + rand()%(values[0].size() - 3)) / 4;

		int y1 = 1 + rand()%(values[0].size() - 3);
		int y2 = 1 + rand()%(values[0].size() - 3);
		int y3 = 1 + rand()%(values[0].size() - 3);
		int y4 = 1 + rand()%(values[0].size() - 3);
		int y5 = (1 + rand()%(values.size() - 3) + 1 + rand()%(values[0].size() - 3)) / 4;

		set_boundary_shape(x1,y1,x5,y5,new_shape,x2,x3,x4,y2,y3,y4);
	}
	} ///end of switch
}

//////
//////
//////

// BOUNDARY CONDITION FUNCTIONS SHOULD BE WRITTEN ABOVE

//////
//////
//////

double Grid::get_average_value(matrix &grid) {
	double sum = 0.;
	int entries = 0;
	for(int x = 1; x < grid.size() - 1; x++) {
		for(int y = 1; y < grid[0].size() - 1; y++) {
			if(grid[x][y].boundary == true && grid[x][y].flag == 1) {sum += grid[x][y].value;
			grid[x][y].flag = 0; entries++;}
		}
	}
	return (double) sum/entries;
}

void Grid::set_conductor(int x, int y, int dx, int dy, Shape shape) {
	set_conductor(x,y,dx,dy,shape,0,0,0,0,0,0);}

void Grid::set_conductor(int x, int y, int dx, int dy, Shape shape, int x1, int x2, int x3, int y1, int y2, int y3) {
	set_boundary_shape(x,y,dx,dy,shape, x1, x2, x3, y1, y2, y3);
	double val = get_average_value(values);
	set_boundary_shape(x,y,dx,dy,val,shape, x1, x2, x3, y1, y2, y3);
}


//Print ASCII table with MINIMAL formatting

void Grid::print_values() {
	cout << fixed;
	cout << endl;
	for (int y = 0; y <= values[0].size() - 1; y++) {
		cout << "[	";
		for (int x = 0; x < values.size(); x++) {
			cout << setprecision(2) << values[x][y].value << "	";
		}
		cout << "	]" << endl;
	}
	cout << endl;
}

//Print table with gnuplot matrix formatting. Plot in gnuplot by saving this to
//a file (let's call it data.dat) and calling in gnuplot:

//	plot 'data.dat' matrix with image

void Grid::print_gnuplot_values() {
	cout << fixed;
	for (int y = 0; y <= values[0].size() - 1; y++) {
		for (int x = 0; x < values.size(); x++) {
			cout << setprecision(2) << values[x][y].value << "	";
		}
		cout << endl;
	}
}

//prints to file sprecified in finite_difference.cc - lets us plot vector field
void Grid::print_all_to(string filename) {
	ofstream outdata;
	outdata.open(filename.c_str());
	if (outdata.is_open()) {
		for (int x = 0; x < values.size(); x++) {
			for (int y = 0; y < values[0].size(); y++) {

				outdata << x << "\t" << y << "\t" << gradients[x][y].dx << "\t"
						<< gradients[x][y].dy << "\t" << gradients[x][y].e_size
						<< "\t" << values[x][y].value << endl;
			}
		}
		outdata.close();

	}

	else
		cout << "unable to open file" << endl;

}

void Grid::print_matrix_to(string filename) {
	ofstream outdata;
	outdata.open(filename.c_str());
	if (outdata.is_open()) {
		for (int y = 0; y < values.size(); y++) {
			for (int x = 0; x < values[0].size(); x++) {

				outdata << values[x][y].value << "\t";
			}
			outdata << "\n";
		}
		outdata.close();
	}

	else
		cout << "unable to open file" << endl;

}

void Grid::print_points() {
	cout << fixed;
	cout << endl;
	for (int y = 0; y <= points[0].size() - 1; y++) {
		cout << "[	";
		for (int x = 0; x < points.size(); x++) {
			cout << setprecision(0) << points[x][y].get_x() << ","
					<< points[x][y].get_y() << "	";
		}
		cout << "	]" << endl;
	}
	cout << endl;
}
