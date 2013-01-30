#include <cmath>
#include <iostream>
#include <vector>
#include <iomanip>

using namespace std;

	//Data structures to be used for grid

struct Value {

	double value;
	bool boundary;
	bool accessible;

};
		
class Coordinate {

	private:
	double xcoor;
	double ycoor;

	public:
	void set_x(double i) {xcoor = i;}
	void set_y(double j) {ycoor = j;}
	void set_xy(double i, double j) {xcoor = i; ycoor = j;}
	double get_x() {return xcoor;}
	double get_y() {return ycoor;}

	double distance(Coordinate two) {
		return sqrt( (xcoor - two.get_x()) * (xcoor - two.get_x()) + (ycoor - two.get_y()) * (ycoor - two.get_y()) );
	}

};

	//Use convention grid[x][y] for coordinate system

typedef vector<vector<Value> > matrix;
typedef vector<vector<Coordinate> > coordinate_matrix;

	//Silly round function so that I can control exactly how it works
	
int round_own(double a) {return int(a + 0.5);}

double Average_value(vector<Value> vec) {
	double total = 0;
	for(int i = 0; i < vec.size(); i++){
		total += vec[i].value;
	}
	return total/vec.size();
}

double Total_value(vector<Value> vec) {
	double total = 0;
	for(int i = 0; i < vec.size(); i++){
		total += vec[i].value;
	}
	return total;
}

double Total_value(vector<double> vec) {
	double total = 0;
	for(int i = 0; i < vec.size(); i++){
		total += vec[i];
	}
	return total;
}

double Average_value(vector<double> vec) {
	double total = 0;
	for(int i = 0; i < vec.size(); i++){
		total += vec[i];
	}
	return total/vec.size();
}

	//Used for the Finite_Difference class. Might also be used for other methods later

struct Iteration {

	matrix it;
	double error;

};

	//Save each grid as two separate matrices, one with values and one with coordinates

class Grid {

	private:
	coordinate_matrix points;
	matrix values;

	public:

	//Create a (x+1)*(y+1) grid. The convention is that calling load_grid(x,y) means that
	//matrix[x][y] is an accessible element. Makes sense if you think of it as a coordinate
	//system (at least to me)

	void load_grid(unsigned int x, unsigned int y) {
		unsigned int ix = x+1;
		unsigned int iy = y+1;
		vector<Value> dummy_vec_val;
		Value dummy_val;
		dummy_val.value = 1;
		dummy_val.boundary = false;
		dummy_val.accessible = true;
		while(iy > 0){
			dummy_vec_val.push_back(dummy_val);
			iy--;
		}
		while(ix > 0){
			values.push_back(dummy_vec_val);
			ix--;
		}
		Coordinate coordinate;
		vector<Coordinate> dummy_vec_coord;
		while(ix <= x){
			for (int z = 0; z <= y; z++) {
				coordinate.set_x((double)ix);
				coordinate.set_y(z);
				dummy_vec_coord.push_back(coordinate);
			}
			points.push_back(dummy_vec_coord);
			dummy_vec_coord.clear();
			ix++;
		}
	}

	//Set range (so that it's possible to use a different increment than 1). Not really used at the moment

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

	//Set value of individual cell without making it a boundary point

	void set_value(unsigned int x, unsigned int y, double val) {
		if(x < values.size() && y < values[0].size())values[x][y].value = val;
		else cout << "Outside of range." << endl;
	}

	//Make a cell a boundary point without changing its value

	void set_boundary(unsigned int x, unsigned int y, bool bound) {
		if(x < values.size() && y < values[0].size())values[x][y].boundary = bound;
		else cout << "Outside of range." << endl;
	}

	//Set both value and make boundary point (most commonly used I imagine)

	void set_boundary_value(unsigned int x, unsigned int y, double val) {
		if (x < values.size() && y < values[0].size()){
			values[x][y].boundary = true;
			values[x][y].value = val;
		}
		else cout << "Outside of range." << endl;
	}

	//Same as above but accepts doubles (so if you for some reason want to define
	//a boundary shape in your own code you won't have to round floats all the time)

	void set_boundary_value_float(double xd, double yd, double val) {
		unsigned int x = round_own(abs(xd));
		unsigned int y = round_own(abs(yd));
		if(x < values.size() && y < values[0].size()){
			values[x][y].boundary = true;
			values[x][y].value = val;
		}
		else cout << "Outside of range." << endl;
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

	void set_flow(double left, double right) {
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

	//Create an inaccessible circle

	void set_circle_noflow(int x, int y, unsigned int r, double val) {
		if(x - r < 0 || x + r > values.size() - 1 || y - r < 0 || y + r > values[0].size() - 1)cout << "Out of range." << endl;
		else {
			for (int xs = x-r; xs<=x+r; xs++) {
				for (int ys = y-r; ys<=y+r; ys++) {
					Coordinate xy;
					xy.set_xy(xs,ys);
					Coordinate mid;
					mid.set_xy(x,y);
					if( mid.distance(xy) < r ){values[xs][ys].value = val; values[xs][ys].accessible = false;}
				}
			}
		}
	}

	//Create a circle with a constant value

	void set_circle(int x, int y, unsigned int r, double val) {
		if(x - r < 0 || x + r > values.size() - 1 || y - r < 0 || y + r > values[0].size() - 1)cout << "Out of range." << endl;
		else {
			for (int xs = x-r; xs<=x+r; xs++) {
				for (int ys = y-r; ys<=y+r; ys++) {
					Coordinate xy;
					xy.set_xy(xs,ys);
					Coordinate mid;
					mid.set_xy(x,y);
					if( mid.distance(xy) < r ){values[xs][ys].value = val; values[xs][ys].boundary = true;}
				}
			}
		}
	}

	//Same as above but semicircle pointed up etc.

	void set_halfcircle_north(int x, int y, unsigned int r, double val) {
		if(x - r < 0 || x + r > values.size() - 1 || y < 0 || y + r > values[0].size() - 1)cout << "Out of range." << endl;
		else {
			for (int xs = x-r; xs<=x+r; xs++) {
				for(int ys = y; ys<=y+r; ys++) {
					Coordinate xy;
					xy.set_xy(xs,ys);
					Coordinate mid;
					mid.set_xy(x,y);
					if( mid.distance(xy) < r ){values[xs][ys].value = val; values[xs][ys].boundary = true;}
				}
			}
		}
	}

	void set_halfcircle_south(int x, int y, unsigned int r, double val) {
		if(x - r < 0 || x + r > values.size() - 1 || y - r < 0 || y > values[0].size() - 1)cout << "Out of range." << endl;
		else {
			for (int xs = x-r; xs<=x+r; xs++) {
				for(int ys = y-r; ys<=y; ys++) {
					Coordinate xy;
					xy.set_xy(xs,ys);
					Coordinate mid;
					mid.set_xy(x,y);
					if( mid.distance(xy) < r ){values[xs][ys].value = val; values[xs][ys].boundary = true;}
				}
			}
		}
	}

	void set_halfcircle_east(int x, int y, unsigned int r, double val) {
		if(x < 0 || x + r > values.size() - 1 || y - r < 0 || y > values[0].size() - 1)cout << "Out of range." << endl;
		else {
			for (int xs = x; xs<=x+r; xs++) {
				for(int ys = y-r; ys<=y+r; ys++) {
					Coordinate xy;
					xy.set_xy(xs,ys);
					Coordinate mid;
					mid.set_xy(x,y);
					if( mid.distance(xy) < r ){values[xs][ys].value = val; values[xs][ys].boundary = true;}
				}
			}
		}
	}

	void set_halfcircle_west(int x, int y, unsigned int r, double val) {
		if(x - r < 0 || x > values.size() - 1 || y - r < 0 || y > values[0].size() - 1)cout << "Out of range." << endl;
		else {
			for (int xs = x-r; xs<=x; xs++) {
				for(int ys = y-r; ys<=y+r; ys++) {
					Coordinate xy;
					xy.set_xy(xs,ys);
					Coordinate mid;
					mid.set_xy(x,y);
					if( mid.distance(xy) < r ){values[xs][ys].value = val; values[xs][ys].boundary = true;}
				}
			}
		}
	}

	//Sets a rectangle with lines at x1,x2,y1&y2
	void set_rectangle(int x1, int y1, int x2, int y2, double val){
	  if(x1 > values.size()-1 || x2 > values.size()-1 || y1 > values.size()-1 || y2 > values.size()-1) cout << "Out of range." << endl;
	  else{
	    for(int xs=min(x1,x2); xs<=max(x1,x2); xs++){
	      for(int ys=min(y1,y2); ys<=max(y1,y2); ys++){
		values[xs][ys].value = val;
		values[xs][ys].boundary = true;
	      }
	    }
	  }
	}
	//Sets an isosceles triangle pointing up or down.
	// x1 & x2 are the x-coords of the corners on the horizontal base
	//y_base and y_tip y coords of base and tip
	void set_isosceles(int x1, int x2, int y_base, int y_tip, double val){
	  if(x1 > values.size()-1 || x2 > values.size()-1 || y_base > values.size()-1 || y_tip > values.size()-1) cout << "Out of range." << endl;
	  else{
	    double slope = (double)(y_tip - y_base)/(0.5*abs(x1-x2)); 
	    int xc=(x1+x2)/2;
	    for(int xs=min(x1,x2); xs<=max(x1,x2); xs++){
	      for(int ys=min(y_tip,y_base); ys<=max(y_tip,y_base); ys++){
		if(y_tip > y_base && ys<=y_tip+slope*(xs-xc) && ys <= y_tip-slope*(xs-xc)){
		  values[xs][ys].value = val;
		  values[xs][ys].boundary = true;
		}	
		if(y_tip < y_base && ys>=y_tip+slope*(xs-xc) && ys >= y_tip-slope*(xs-xc)){
		    values[xs][ys].value=val; 
		    values[xs][ys].boundary = true;
		  }
		}
	      }
	    }
	  }
	  
       		  
	//sets an ellipse with centre at x and y and rx and ry are distance
	//from centre to min & max x values and y values respectively	    
     	void set_ellipse(int x, int y, unsigned int rx, unsigned int ry, double val){
	  if(x-rx<0 || y-ry<0 || x+rx>values.size()-1 || y+ry>values.size()-1 )cout << "Out of range." << endl;
	  for(int xs=x-rx; xs<=x+rx; xs++){
	    for(int ys=y-ry; ys<=y+ry; ys++){
	      if(pow(((double)(xs-x)/rx),2)+pow(((double)(ys-y)/ry),2) <= 1){
		values[xs][ys].value=val;
		values[xs][ys].boundary = true;
	      }
	    }
	  }
	}
		//////
		//////
		//////

		// BOUNDARY CONDITION FUNCTIONS SHOULD BE WRITTEN ABOVE

		//////
		//////
		//////
	
	//Return stuff, change stuff and so on

	coordinate_matrix get_coordinates() {return points;}
	matrix get_values() {return values;}

	void set_coordinates(coordinate_matrix coords) {points = coords;}
	void set_values(matrix vals) {values = vals;}

	//Print ASCII table with MINIMAL formatting

	void print_values() {
		cout << fixed;
		cout << endl;
		for ( int y = 0; y <= values[0].size() - 1; y++) {
			cout << "[	";
			for ( int x = 0; x < values.size(); x++) {
				cout << setprecision (2) << values[x][y].value << "	";
			}
			cout << "	]" << endl;
		}
		cout << endl;
	}
	
	//Print table with gnuplot matrix formatting. Plot in gnuplot by saving this to
	//a file (let's call it data.dat) and calling in gnuplot:

	//	plot 'data.dat' matrix with image

	void gnuplot_values() {
		cout << fixed;
		for ( int y = 0; y <= values[0].size() - 1; y++) {
			for ( int x = 0; x < values.size(); x++) {
				cout << setprecision (2) << values[x][y].value << "	";
			}
			cout << endl;
		}
	}

	void print_points() {
		cout << fixed;
		cout << endl;
		for ( int y = 0; y <= points[0].size() - 1; y++) {
			cout << "[	";
			for ( int x = 0; x < points.size(); x++) {
				cout << setprecision (0) << points[x][y].get_x() << "," << points[x][y].get_y() << "	";
			}
			cout << "	]" << endl;
		}
		cout << endl;
	}
};
