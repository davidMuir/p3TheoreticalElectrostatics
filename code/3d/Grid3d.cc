#include "Grid3d.h"

using namespace std;

Grid3d::Grid3d() : Grid3d::Grid3d(50,50,50){}

Grid3d::Grid3d(unsigned int x, unsigned int y, unsigned int z){
  unsigned int ix=x+1;
  unsigned int iy=y+1;
  unsigned int iz=z+1;
  vector<vector<Value> > dummy_mat_val;
  vector<Value> dummy_vec_val;
  Value dummy_val;
  dummy_val.value = 1;
  dummy_val.boundary=false;
  dummy_val.accessible = true;
  while(iz > 0){
    dummy_vec_val.push_back(dummy_val);
    iz--;
  }
  while(iy > 0){
    dummy_mat_val.push_back(dummy_vec_val);
    iy--;
  }
  while(ix > 0){
    values3d.push_back(dummy_mat_val);
    ix--;
  }
  Coordinate3d coordinate;
  vector<vector<Coordinate3d> > dummy_mat_coord;
  vector<Coordinate3d> dummy_vec_coord;
  while(ix <= x){
    for(int y1=0; y1 <= y; y1++){
      for(int z1=0; z1 <= z; z1++){
	coordinate.set_xyz((double)ix, y1, z1);
	dummy_vec_coord.push_back(coordinate);
      }
      dummy_mat_coord.push_back(dummy_vec_coord);
      dummy_vec_coord.clear();
    }
    points3d.push_back(dummy_mat_coord);
    dummy_mat_coord.clear();
    ix++;
  }
  Grad dummy_grad;
  vector<Grad> dummy_vec_grad;
  vector<vector<Grad> > dummy_mat_grad;
  dummy_grad.dx=0.5;
  dummy_grad.dy=0.5;
  dummy_grad.dz=0.5;
  ix=x+1;

  iy=y+1;
  iz=z+1;
  while(iz > 0){
    dummy_vec_grad.push_back(dummy_grad);
    iz--;
  }
  while(iy > 0){
    dummy_mat_grad.push_back(dummy_vec_grad);
    iy--;
  }
  while(ix > 0){
    gradients3d.push_back(dummy_mat_grad);
    ix--;
  }
}

Grid3d::~Grid3d(){}

void Grid3d::set_range(double x, double y, double z){ 
  //will write later not essential
}

void Grid3d::set_value(unsigned int x, unsigned int y, unsigned int z, double val){
  if (x<values3d.size() && y<values3d[0].size() && z<values3d[0][0].size())
    values3d[x][y][z].value = val;
  else
    cout << "Outside of range." << endl;
}

void Grid3d::set_boundary_value(unsigned int x, unsigned int y, 
				unsigned int z, double val){
  if(x<values3d.size() && y< values3d[0].size() && z<values3d[0][0].size()){
    values3d[x][y][z].boundary = true;
    values3d[x][y][z].value=val;
  }
  else cout << "Outside of range." << endl;
}

void Grid3d::set_flow(double left, double right){
  double gradient = (right-left)/(values3d.size()-1);
  for ( int y=0; y<values3d[0].size(); y++){
    for (int z=0; z<values3d[0][0].size(); z++){
      values3d[0][y][z].value = left;
      values3d[0][y][z].boundary = true;
      values3d[values3d.size()-1][y][z].value = right;
      values3d[values3d.size()-1][y][z].boundary = true;
    }
  }
  for (int x=0; x<values3d.size(); x++){
    for (int z=0; z<values3d[0][0].size(); z++){
      values3d[x][0][z].value = left +x*gradient;
      values3d[x][0][z].boundary = true;
      values3d[x][values3d[0].size()-1][z].value = left +x*gradient;
      values3d[x][values3d[0].size()-1][z].boundary = true;
    }
    for (int y=0; y<values3d[0].size(); y++){
      values3d[x][y][0].value = left + x*gradient;
      values3d[x][y][0].boundary = true;
      values3d[x][y][values3d[0][0].size()-1].value=left +x*gradient;
      values3d[x][y][values3d[0][0].size()-1].boundary=left +x*gradient;
    }
  }
}
  coordinate_matrix3d Grid3d::get_coordinates(){
    return points3d;
  }
  matrix3d Grid3d::get_values(){
    return values3d;
  }
  grad_matrix3d Grid3d::get_gradients(){
    return gradients3d;
  }
  void Grid3d::set_coordinates(coordinate_matrix3d coords){
    points3d=coords;
  }
void Grid3d::set_values(matrix3d vals){
  values3d=vals;
}
void Grid3d::set_gradients(grad_matrix3d grads){
  gradients3d=grads;
}

void Grid3d::set_sphere(int x, int y, int z, unsigned int r, double val){
  if(x<r||x+r>values3d.size()||y<r||y+r>values3d[0].size()||z<r||z+r>values3d[0][0].size()){
  cout << "Out of range." << endl;}
  else{
    for(int xs=x-r;xs<=x+r;xs++){
      for(int ys=y-r;ys<=y+r;ys++){
	for(int zs=z-r;zs<=z+r;zs++){
	  if(xs*xs+ys*ys+zs*zs<=r*r){
	    values3d[xs][ys][zs].boundary = true;
	    values3d[xs][ys][zs].value = val;
	  }
	}
      }
    }
  }
}


void Grid3d::print_all_to(string filename) {
	ofstream outdata;
	outdata.open(filename.c_str());
	if (outdata.is_open()) {
		for (int x = 0; x < values3d.size(); x++) {
		  for (int y = 0; y < values3d[0].size(); y++) {
		    for (int z = 0; z < values3d[0][0].size(); z++){

		      outdata << x << "\t" << y << "\t" << z
			      << "\t" << gradients3d[x][y][z].dx
			      << "\t" << gradients3d[x][y][z].dy 
			      << "\t" << gradients3d[x][y][z].dz
			      << "\t" << gradients3d[x][y][z].e_size
			      << "\t" << values3d[x][y][z].value
			      << endl;
		    }	  
		  }				
		}		
	      		outdata.close();
		
	}

	else
		cout << "unable to open file" << endl;

}




void Grid3d::print_vector_field(string filename) {
	ofstream outdata;
	outdata.open(filename.c_str());
	if (outdata.is_open()) {
		for (int x = 0; x < values3d.size(); x=x+10) {
		  for (int y = 0; y < values3d[0].size(); y=y+10) {
		    for (int z = 0; z < values3d[0][0].size(); z=z+10){

		      outdata << x << "\t" << y << "\t" << z
			      << "\t" << gradients3d[x][y][z].dx
			      << "\t" << gradients3d[x][y][z].dy 
			      << "\t" << gradients3d[x][y][z].dz
			      << "\t" << gradients3d[x][y][z].e_size
			      << "\t" << values3d[x][y][z].value
			      << endl;
		    }	  
		  }				
		}		
	      		outdata.close();
		
	}

	else
		cout << "unable to open file" << endl;

}

void Grid3d::print_matrices(string filename) {
  for (int z = 0; z < values3d[0][0].size(); z++){
    std::stringstream s;
    s<<"matrix_z="<<z<<".dat";
    ofstream outdata(s.str().c_str(), ios::trunc|ios::out);
    for (int y = 0; y < values3d[0].size(); y++){
      for (int x =0; x < values3d.size(); x++){

	outdata << values3d[x][y][z].value << "\t";
      }
      outdata << endl;
    }
    outdata.close();
  }
}




 
