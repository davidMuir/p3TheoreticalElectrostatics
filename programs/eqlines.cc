#include "Algorithms/Asymmetric_Finite_Volume.h"
#include "Utils/Gnuplot.h"
#include "Algorithms/Finite_Difference.h"
#include "Algorithms/Fast_Finite_Difference.h"
#include "Errors/Compare.h"
#include "Utils/Conductors.h"
#include <ctime> 

using namespace std;
  
int main() {    
        
	int N = 21 ;     // number of eq.p. lines
	int n = 200;
	int m = 200; 
     
   
	double Emax=100;
	double Emin=-100; 
   
	Grid first_grid(n,m);

	first_grid.set_flow(Emax, Emin);   
	first_grid.set_boundary_shape(100,100,50,0,0,circle);   

	Finite_Difference fd (first_grid);
	fd.set_precision(0.00001); 
	fd.set_maxit(10000);
	  Grid sol = fd.get_solution();
   
	Gnuplot gp(sol);
	sol.efield(); 
	sol.print_all_to("results2.dat");
	sol.equip_values(N,n,m,Emax);
	sol.print_all_to("results.dat");
// 	sol.print_efield_to("eq_lines.dat", N);
//	sol.print_figure_to("figure.dat", 1); // 2 - the number of figures
   
   
	/*gp.a dd_command("set term jpeg");
	gp.add_command("set output 'test.jpg'");
	gp.add_command("set palette defined");
	gp.add_command("plot 'results.dat' with image, 'eq_lines.dat' with points ls -1"); // white = ls -3; black = ls -1; red = ls 1; green = 2; blue = ls 3; violet = ls 4;
	gp.sendString();*/
    
	return 0;
    
	}
