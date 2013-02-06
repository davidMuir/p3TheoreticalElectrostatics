<<<<<<< HEAD
#include "Algorithms/Asymmetric_Finite_Volume.h"
//#include "Utils/gnuplot-iostream.h"
=======
#include "Algorithms/Finite_Difference.h"
>>>>>>> cd38be1918a97e584f159577f49088c2cf0819c7

using namespace std;

int main() {

<<<<<<< HEAD
	int n = 50;
	int m = 50;

	Grid first_grid(n,m);
	first_grid.set_flow(50, -50);
	first_grid.set_circle_noflow(25,25,10,100);

	Asymmetric_Finite_Volume fd (first_grid);
	fd.set_precision(0.2);
	fd.set_maxit(10000);
	Grid sol = fd.get_solution();
	popen("gnuplot ../data/asym.gnu","r");
	//cout << fd.get_iterations() << endl;
//	sol.print_gnuplot_values();
	//sol.print_all_to("results.dat");
=======
	int n = 100;
	int m = 100;

	Grid first_grid(n,m);
	first_grid.set_flow(100, -100);
	first_grid.set_circle(50,50,20,0);

	Finite_Difference fd (first_grid);
	fd.set_precision(0.01);
	fd.set_maxit(10000);
	Grid sol = fd.get_solution();
	//cout << fd.get_iterations() << endl;
	sol.efield();
	sol.print_gnuplot_values();
	sol.print_matrix_to("matrix_circle_fd.dat");
	sol.print_all_to("all_circle_fd.dat");
>>>>>>> cd38be1918a97e584f159577f49088c2cf0819c7
	

	return 0;

	}
