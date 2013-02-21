#include "Algorithms/Asymmetric_Finite_Volume.h"
#include "Utils/Gnuplot.h"
#include "Algorithms/Finite_Difference.h"
#include "Algorithms/Fast_Finite_Difference.h"
#include "Errors/Compare.h"
#include <ctime>

using namespace std;

int main() {

	int n = 1000;
	int m = 1000;

	Grid first_grid(n,m);

	first_grid.set_flow(50, -50);
	first_grid.set_boundary_shape(500,500,25,0,0,circle);

	Grid entry(n,m);
	entry.set_flow(50, -50);
	Analytic an(entry);
	an.solve(500,500,10,0,1);
	Grid analytic = an.get_solution();

	Fast_Finite_Difference ffd (first_grid);
	ffd.set_precision(0.00001);
	ffd.set_maxit(10000);

	//Grid shape = first_grid.get_boundary_grid(50,50,25,25,10,0,circle);

//	sol.print_gnuplot_values();
//	sol.print_matrix_to("matrix_circle_fd.dat");


	Grid sol_ffd = ffd.get_solution();
//	sol_fd.efield();
	Gnuplot gp(sol_ffd);
	gp.add_comment("testing comment");
	gp.add_command("set term jpeg");
	gp.add_command("set output 'test.jpg'");
	gp.add_command("set xrange [450:550]");
	gp.add_command("set yrange [440:550]");
	gp.add_command("unset key");
	gp.add_command("set cbrange [-50:50]");
	gp.add_command("set palette color");
	gp.add_command("set palette defined");
	gp.add_plot();
	gp.sendString();

//	Asymmetric_Finite_Volume fv(first_grid);
//	Grid sol_fv = fv.get_solution();

	Grid comp_fd = find_err(analytic , sol_ffd);
	//comp_fd.print_matrix_to("fd_err.dat");
	cout << "average error in finite diff " << average_grid(comp_fd) << endl;
	//comp_ffd.print_matrix_to("ffd_err.dat");

	/*
	Asymmetric_Finite_Volume fv(first_grid);
	fv.set_precision(0.00001);
	fv.set_maxit(10000);
	Grid sol_fv = fv.get_solution();
	Grid comp_fv = find_err(analytic, sol_fv);
	comp_fv.print_matrix_to("fv_err.dat");


	cout << "average error finite vol " << average_grid(comp_fv) << endl;
	*/

	return 0;

	}
