#include "Algorithms/Asymmetric_Finite_Volume.h"
#include "Utils/Gnuplot.h"
#include "Algorithms/Finite_Difference.h"
#include "Errors/Compare.h"

using namespace std;

int main() {

	int n = 100;
	int m = 100;

	Grid first_grid(n,m);

	first_grid.set_flow(50, -50);
	first_grid.set_boundary_shape(50,50,10,0,0,circle);

	Finite_Difference fd (first_grid);
	fd.set_precision(0.00001);
	fd.set_maxit(10000);

	Grid sol_fd = fd.get_solution();
	//cout << fd.get_iterations() << endl;
	sol_fd.efield();

	Asymmetric_Finite_Volume fv(first_grid);
	Grid sol_fv = fv.get_solution();

	Grid entry(m,n);
	entry.set_flow(50, -50);
	Analytic an(entry);
	an.solve(50,50,20,0,1);
	Grid analytic = an.get_solution();

	Grid comp_fd = find_err(analytic , sol_fd);
	Grid comp_fv = find_err(analytic, sol_fv);


	comp_fd.print_matrix_to("fd_err.dat");
	comp_fv.print_matrix_to("fv_err.dat");

	//	sol.print_gnuplot_values();
	//	sol_fd.print_matrix_to("matrix_circle_fd.dat");
	//	sol.print_all_to("all_circle_fd.dat");


	
//	sol.print_gnuplot_values();
//	sol.print_matrix_to("matrix_circle_fd.dat");
//	sol.print_all_to("all_circle_fd.dat");

	Gnuplot gp(sol_fd);
	gp.add_comment("testing comment");
	gp.add_command("set term jpeg");
	gp.add_command("set output 'test.jpg'");
	gp.add_plot();
	gp.save_string("foo.gnu");
	gp.sendString();

	Gnuplot rf(sol_fd);
	rf.read_file("foo.gnu");
	rf.save_string("bar.gnu");

	//	sol.print_gnuplot_values();
	//	sol.print_matrix_to("matrix_circle_fd.dat");
	//	sol.print_all_to("all_circle_fd.dat");
	
	return 0;

	}
