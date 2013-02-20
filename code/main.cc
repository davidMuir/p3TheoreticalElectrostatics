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

	Grid entry(m,n);
	entry.set_flow(50, -50);
	Analytic an(entry);
	an.solve(50,50,10,0,1);
	Grid analytic = an.get_solution();

	Grid comp_fd = find_err(analytic , sol_fd);
//	Grid comp_fv = find_err(analytic, sol_fv);
	Grid comp_ffd = find_err(analytic,sol_fd2);
	Grid comp_alg = find_err(sol_fd,sol_fd2);


//	comp_fd.print_matrix_to("fd_err.dat");
//	comp_fv.print_matrix_to("fv_err.dat");

	//	sol.print_gnuplot_values();
	//	sol_fd.print_matrix_to("matrix_circle_fd.dat");
	//	sol.print_all_to("all_circle_fd.dat");


	
//	sol.print_gnuplot_values();
//	sol.print_matrix_to("matrix_circle_fd.dat");
//	sol.print_all_to("all_circle_fd.dat");

	Gnuplot gp(analytic);
	gp.add_comment("testing comment");
	gp.add_command("set term jpeg");
	gp.add_command("set output 'analytic.jpg'");
	gp.add_plot();
	gp.sendString();

	Gnuplot gp2(sol_fd2);
	gp2.add_comment("testing comment");
	gp2.add_command("set term jpeg");
	gp2.add_command("set output 'ffd.jpg'");
	gp2.add_plot();
	gp2.sendString();

	Gnuplot gp3(comp_ffd);
	gp3.add_command("set term jpeg");
	gp3.add_command("set output 'analyticffd.jpg'");
	gp3.add_plot();
	gp3.sendString();

	Gnuplot gp4(comp_fd);
	gp4.add_command("set term jpeg");
	gp4.add_command("set output 'analyticfd.jpg'");
	gp4.add_plot();
	gp4.sendString();

	Gnuplot gp5(comp_alg);
	gp5.add_command("set term jpeg");
	gp5.add_command("set output 'comparison.jpg'");
	gp5.add_plot();
	gp5.sendString();


	//	sol.print_gnuplot_values();
	//	sol.print_matrix_to("matrix_circle_fd.dat");
	//	sol.print_all_to("all_circle_fd.dat");
	
	return 0;

	}
