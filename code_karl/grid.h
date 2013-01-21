#include <cmath>
#include <iostream>
#include <vector>
#include <iomanip>

using namespace std;

struct Value {

	double value;
	bool boundary;

	};

class Coordinate {

	private:
	double xcoor;
	double ycoor;

	public:
	void set_x(double i) {xcoor = i;}
	void set_y(double j) {ycoor = j;}
	double get_x() {return xcoor;}
	double get_y() {return ycoor;}

	double distance(Coordinate two) {
		return sqrt( (xcoor - two.get_x()) * (xcoor - two.get_x()) + (ycoor - two.get_y()) * (ycoor - two.get_y()) );
		}

	};

	//Use convention grid[x][y] for coordinate system
typedef vector<vector<Value> > matrix;
typedef vector<vector<Coordinate> > coordinate_matrix;

class Grid {

	private:
	coordinate_matrix points;
	matrix values;

	public:
	void load_grid(unsigned int x, unsigned int y) {
		unsigned int it = x;
		unsigned int itt = y;
		vector<Value> dummy;
		Value dummy1;
		while(itt > 0){dummy1.value = 1; dummy1.boundary = false; dummy.push_back(dummy1); itt--;}
		while(it > 0){values.push_back(dummy); it--;}
		Coordinate coordinate;
		vector<Coordinate> dummy2;
		while(it < x){
			for (int z = 0; z < y; z++) {coordinate.set_x((double)it); coordinate.set_y(z); dummy2.push_back(coordinate);}
			points.push_back(dummy2);
			dummy2.clear();
			it++;
			}
		}

	void set_range(double x, double y) {
		unsigned int x_size = points.size() - 1;
		unsigned int y_size = points[0].size() - 1;
		double x_mult = x/x_size;
		double y_mult = y/y_size;
		for(int it1 = 0; it1 < x_size + 1; it1++) {
			for(int it2 = 0; it2 < y_size + 1; it2++) {
				double x_val = points[it1][it2].get_x();
				double y_val = points[it1][it2].get_y();
				if(x_val != 0)points[it1][it2].set_x(x_val * x_mult);
				if(y_val != 0)points[it1][it2].set_y(y_val * y_mult);
				}
			}
		}


	void set_value(unsigned int x, unsigned int y, double val) {
		if(x < values.size() && y < values[0].size())values[x][y].value = val;
		else cout << "Outside of range." << endl;
		}

	void set_boundary(unsigned int x, unsigned int y, bool bound) {
		if(x < values.size() && y < values[0].size())values[x][y].boundary = bound;
		else cout << "Outside of range." << endl;
		}

	void set_boundary_value(unsigned int x, unsigned int y, double val) {
		if(x < values.size() && y < values[0].size())
			{values[x][y].boundary = true; values[x][y].value = val;}
		else cout << "Outside of range." << endl;
		}

	coordinate_matrix get_coordinates() {return points;}
	matrix get_values() {return values;}

	void set_coordinates(coordinate_matrix coords) {points = coords;}
	void set_values(matrix vals) {values = vals;}

	void print_values() {
		cout << fixed;
		cout << endl;
		for ( int y = values[0].size() - 1; y >= 0; y--) {
			cout << "[	";
			for ( int x = 0; x < values.size(); x++) {
				cout << setprecision (2) << values[x][y].value << "	";
				}
			cout << "	]" << endl;
			}
		cout << endl;
		}

	void gnuplot_values() {
		cout << fixed;
		for ( int y = values[0].size() - 1; y >= 0; y--) {
			for ( int x = 0; x < values.size(); x++) {
				cout << setprecision (2) << values[x][y].value << "	";
				}
			cout << endl;
			}
		}

	void print_points() {
		cout << fixed;
		cout << endl;
		for ( int y = points[0].size() - 1; y >= 0; y--) {
			cout << "[	";
			for ( int x = 0; x < points.size(); x++) {
				cout << setprecision (0) << points[x][y].get_x() << "," << points[x][y].get_y() << "	";
				}
			cout << "	]" << endl;
			}
		cout << endl;
		}
	};
