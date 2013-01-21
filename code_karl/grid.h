#include <cmath>
#include <iostream>
#include <vector>
#include <iomanip>

using namespace std;

class Coordinate {

	private:
	double xcoor;
	double ycoor;

	public:
	void set_x(double i) {xcoor = i;}
	void set_y(double j) {ycoor = j;}
	double get_x() {return xcoor;}
	double get_y() {return ycoor;}

	};

	//Use convention grid[x][y] for coordinate system
typedef vector<vector<double> > matrix;
typedef vector<vector<Coordinate> > coordinate_matrix;

class Grid {

	private:
	coordinate_matrix points;
	matrix values;

	public:
	void load_grid(unsigned int x, unsigned int y) {
		unsigned int it = x;
		vector<double> dummy;
		dummy.assign(y, 0);
		while(it > 0){values.push_back(dummy); it--;}
		Coordinate coordinate;
		vector<Coordinate> dummy2;
		while(it < x+1){
			for (int z = 0; z < y+1; z++) {coordinate.set_x((double)it); coordinate.set_y(z); dummy2.push_back(coordinate);}
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
		if(x < values.size() && y < values[0].size())values[x][y] = val;
		else cout << "Outside of range." << endl;
		}

	void print_values() {
		cout << fixed;
		cout << endl;
		for ( int y = values[0].size() - 1; y >= 0; y--) {
			cout << "[	";
			for ( int x = 0; x < values.size(); x++) {
				cout << setprecision (2) << values[x][y] << "	";
				}
			cout << "	]" << endl;
			}
		cout << endl;
		}

	void print_points() {
		cout << fixed;
		cout << endl;
		for ( int y = points[0].size() - 1; y >= 0; y--) {
			cout << "[	";
			for ( int x = 0; x < points.size(); x++) {
				cout << setprecision (1) << points[x][y].get_x() << "," << points[x][y].get_y() << "	";
				}
			cout << "	]" << endl;
			}
		cout << endl;
		}
	};
