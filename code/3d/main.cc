#include "Finite_Difference3d.h"
using namespace std;

int main(){
  int n=100, m=100, o=100;

  Grid3d first_grid(n,m,o);
  first_grid.set_flow(100,-100);
  first_grid.set_sphere(50,50,50,20,0);

  Finite_Difference3d fd (first_grid);
  fd.set_precision(0.01);
  fd.set_maxit(1000);
  Grid3d sol = fd.get_solution();
  sol.print_matrices("matrix.dat");
}
