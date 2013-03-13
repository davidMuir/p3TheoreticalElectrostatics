#include "../Structures/Grid.h"


class Analytic {
 public:
  Analytic(Grid entry){
    grid = entry;

  }
  ~Analytic(){};

  void solve(int x, int y, unsigned int r, double val, double h){
    matrix sol = grid.get_values();
if(x<r || x+r>sol.size()-1 || y<r || y+r>sol[0].size()-1)
      cout << "Out of range" << endl;
 double e_lim = sol[0][sol.size()/2].value*h/x;

    for(int xs=0; xs<sol.size(); xs++){
      for(int ys=0; ys<sol[0].size();ys++){
	Coordinate xy;
	xy.set_xy(xs/h,ys/h);
	Coordinate mid;
	mid.set_xy(x/h,y/h);
	if(mid.distance(xy) < r/h){
	  sol[xs][ys].value = val;
	}
	else{
	  double dist = mid.distance(xy);
	  sol[xs][ys].value = val + e_lim*(xy.get_x()-mid.get_x())/dist*(r*r/(h*h*dist) - dist);
	}
      }
    }
    solution.set_values(sol);
    solution.set_coordinates(grid.get_coordinates());
    solution.set_gradients(grid.get_gradients());
  }

  Grid get_solution(){
    return solution;
  }




 private:
 Grid solution;
 Grid grid;
 Grid err_grid;
 Grid num_grid;


};

Grid find_err(Grid grid1, Grid grid2){

    matrix m1 = grid1.get_values();
    matrix m2 = grid2.get_values();
    Grid err_grid(m1.size(),m1[0].size());
    if(m1.size()!= m2.size() || m1[0].size() != m2[0].size()){
      cout << "Error: grids not the same size" << endl;
    }else{
      for(int xs=0; xs<m1.size(); xs++){
	for(int ys=0; ys<m1[0].size(); ys++){
	  double val_1 = m1[xs][ys].value;
	  double val_2 = m2[xs][ys].value;
	  err_grid.set_value(xs,ys,abs(val_1-val_2));
	}
      }

      return err_grid;
    }
  }

  Grid find_err_relative(Grid grid1, Grid grid2){

    matrix m1 = grid1.get_values();
    matrix m2 = grid2.get_values();
    Grid err_grid(m1.size(),m1[0].size());
    if(m1.size()!= m2.size() || m1[0].size() != m2[0].size()){
      cout << "Error: grids not the same size" << endl;
    }else{
      for(int xs=0; xs<m1.size(); xs++){
	for(int ys=0; ys<m1[0].size(); ys++){
	  double val_1 = m1[xs][ys].value;
	  double val_2 = m2[xs][ys].value;
	  err_grid.set_value(xs,ys,val_1-val_2);
	}
      }

      return err_grid;
    }
  }

