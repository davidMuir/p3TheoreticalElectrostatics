#include "Algorithms/Asymmetric_Finite_Volume.h"
#include "Utils/Gnuplot.h"
#include "Algorithms/Finite_Difference.h"
#include "Algorithms/Fast_Finite_Difference.h"
#include "Errors/Compare.h"
#include <ctime>

using namespace std;

int main() {

	int n = 100;
	int m = 100;

	Grid first_grid(n,m);
	Grid second_grid(n,m);

	first_grid.set_flow(50, -50);
	first_grid.set_boundary_shape(50,50,10,0,0,circle);

	second_grid.set_flow(50, -50);
	second_grid.set_boundary_shape(50,50,10,0,0,circle);
	Grid entry(n,m);
	entry.set_flow(50, -50);
	Analytic an(entry);
	an.solve(50,50,10,0,1);
	Grid analytic = an.get_solution();

	Finite_Difference fd (first_grid);
	fd.set_precision(0.00001);
	fd.set_maxit(10000);
	Fast_Finite_Difference fd2 (second_grid);
	fd2.set_precision(0.00001);
	fd2.set_maxit(10000);


	std::cout << "Alg 1\n";
	std::clock_t a = std::clock();
	Grid sol_fd = fd.get_solution();
	std::clock_t b = std::clock();
	std::cout << "Alg 2\n";
	Grid sol_fd2 = fd2.get_solution();
	std::clock_t c = std::clock();
	std::cout << "Old: " << (b-a) << " New: " << (c-b) << std::endl;
	std::cout << fd2.get_iterations() << std::endl;
//	sol_fd.efield();

//	Asymmetric_Finite_Volume fv(first_grid);
//	Grid sol_fv = fv.get_solution();

	Grid comp_fd = find_err(analytic , sol_fd);
	comp_fd.print_matrix_to("fd_err.dat");
	cout << "average error in finite diff " << average_grid(comp_fd) << endl;
	Fast_Finite_Difference ffd(first_grid);
	ffd.set_precision(0.00001);
	ffd.set_maxit(10000);
	Grid sol_ffd = ffd.get_solution();
	Grid comp_ffd = find_err(analytic, sol_ffd);
	comp_ffd.print_matrix_to("ffd_err.dat");
	cout << "average error fast fd " << average_grid(comp_ffd) << endl;

	Asymmetric_Finite_Volume fv(first_grid);
	fv.set_precision(0.00001);
	fv.set_maxit(10000);
	Grid sol_fv = fv.get_solution();
	Grid comp_fv = find_err(analytic, sol_fv);
	comp_fv.print_matrix_to("fv_err.dat");


	cout << "average error finite vol " << average_grid(comp_fv) << endl;
	
	return 0;

	}
