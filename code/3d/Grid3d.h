#include <iostream>
#include <vector>
#include <cstdlib>
#include <cmath>
#include <fstream>
#include <iomanip>
#include <string>
#include <sstream>

#ifndef GRID3D_H_
#define GRID3D_H_

class Coordinate3d {
 private:
  double x;
  double y;
  double z;
 public:
  void set_x(double i){x=i;}
  void set_y(double j){y=j;}
  void set_z(double k){z=k;}
  void set_xyz(double i, double j, double k){x=i; y=j; z=k;}
  double get_x(){return x;}
  double get_y(){return y;}
  double get_z(){return z;}
};

struct Value {
  double value;
  bool boundary;
  bool accessible;
};

struct Grad {
  double dx;
  double dy;
  double dz;
  double e_size;
};

typedef std::vector<std::vector<std::vector<Value> > > matrix3d;
typedef std::vector<std::vector<std::vector<Grad> > > grad_matrix3d;
typedef std::vector<std::vector<std::vector<Coordinate3d> > > coordinate_matrix3d;

class Grid3d {
 public:
  Grid3d();
  Grid3d(unsigned int x, unsigned int y, unsigned int z);
  ~Grid3d();

  void set_range(double x, double y, double z);
  void set_value(unsigned int x, unsigned int y, unsigned int z, double val);
  void set_boundary_value(unsigned int x, unsigned int y, unsigned int z, 
			  double val);
  void set_flow(double left, double right);
  void set_coordinates(coordinate_matrix3d coords);
  void set_values(matrix3d vals);
  void set_gradients(grad_matrix3d grads);
  coordinate_matrix3d get_coordinates();
  matrix3d get_values();
  grad_matrix3d get_gradients();

  void set_sphere(int x, int y, int z, unsigned int r, double val);
  void print_all_to(std::string filename);
  void print_vector_field(std::string filename);
  void print_matrices(std::string filename);

 private:
  coordinate_matrix3d points3d;
  grad_matrix3d gradients3d;
  matrix3d values3d;
};


#endif 
  
