#include "Grid.h"

using namespace std;

//Silly round function so that I can control exactly how it works

int Grid::round_own(double a) {
	return int(a + 0.5);
}

Grid::Grid() : Grid::Grid(50,50){}

Grid::Grid(unsigned int x, unsigned int y) {
	unsigned int ix = x + 1;
	unsigned int iy = y + 1;
	vector<Value> dummy_vec_val;
	Value dummy_val;
	dummy_val.value = 1;
	dummy_val.boundary = false;
	dummy_val.accessible = true;
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

Grid::~Grid(){}

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

			dx1 = values[x][y].value
					- values[x + 1][y].value;
			dy1 = values[x][y].value
					- values[x][y + 1].value;
			gradients[x][y].e_size=sqrt(dx1*dx1+dy1*dy1);
			gradients[x][y].dx=dx1/gradients[x][y].e_size;
			gradients[x][y].dy=dy1/gradients[x][y].e_size;
		}
	}
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

//Create a circle with a constant value

void Grid::set_boundary_shape(int x, int y, int r, int z, double val, Shape shape) {

	switch(shape) 
	{

	///CIRCLE
	case circle:
	{
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
					values[xs][ys].boundary = true;
				}
			}
		}
	}
	break;
	}

	//SEMICIRCLES
	case semicircle_north:
	{
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
					values[xs][ys].value = val;
					values[xs][ys].boundary = true;
				}
			}
		}
	}
	break;
	}

	case semicircle_south:
	{
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
					values[xs][ys].value = val;
					values[xs][ys].boundary = true;
				}
			}
		}
	}
	break;
	}

	case semicircle_east:
	{
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
					values[xs][ys].value = val;
					values[xs][ys].boundary = true;
				}
			}
		}
	}
	break;
	}

	case semicircle_west:
	{
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
					values[xs][ys].value = val;
					values[xs][ys].boundary = true;
				}
			}
		}
	}
	break;
	}

	///RECTANGLE
	case rectangle:
	{
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
				values[xs][ys].value = val;
				values[xs][ys].boundary = true;
			}
		}
	}
	break;
	}

	///TRIANGLE
	case triangle:
	{
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
	case ellipse:
	{
	int rx = r;
	int ry = z;
	if (x - rx < 0 || y - ry < 0 || x + rx > values.size() - 1
			|| y + ry > values.size() - 1)
		cout << "Out of range." << endl;
	for (int xs = x - rx; xs <= x + rx; xs++) {
		for (int ys = y - ry; ys <= y + ry; ys++) {
			if (pow(((double) (xs - x) / rx), 2)
					+ pow(((double) (ys - y) / ry), 2) <= 1) {
				values[xs][ys].value = val;
				values[xs][ys].boundary = true;
			}
		}
	}
	break;
	}
	}///end of switch
}

//////
//////
//////

// BOUNDARY CONDITION FUNCTIONS SHOULD BE WRITTEN ABOVE

//////
//////
//////

//Grid Grid::get_boundary_grid(int size_x, int size_y, int x, int y, int dx, int dy, Shape shape) {
//	Grid grid(size_x,size_y);
	

//void Grid::set_conductor(

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

				outdata << x << "\t" << y << "\t" << gradients[x][y].dx
						<< "\t" << gradients[x][y].dy << "\t"
						<< gradients[x][y].e_size << "\t"
						<< values[x][y].value << endl;
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
