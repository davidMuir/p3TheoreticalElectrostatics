<<<<<<< HEAD
=======
#include "Algorithms/Asymmetric_Finite_Volume.h"
#include "Utils/Gnuplot.h"
>>>>>>> 78b591d74860275455bd0cf338ba35d685a6175d
#include "Algorithms/Finite_Difference.h"

using namespace std;

int main() {
<<<<<<< HEAD

=======
>>>>>>> 78b591d74860275455bd0cf338ba35d685a6175d
	int n = 100;
	int m = 100;

	Grid first_grid(n,m);
<<<<<<< HEAD
<<<<<<< HEAD
	first_grid.set_flow(50, -50);
	first_grid.set_boundary_shape(25,25,10,0,0,circle);

	Finite_Difference fd (first_grid);
	fd.set_precision(0.00001);
=======
	first_grid.set_flow(100, -100);
	first_grid.set_circle(50,50,20,0);

	Finite_Difference fd (first_grid);
	fd.set_precision(0.01);
>>>>>>> d143dfda9a7a53bf2f21b318afca1b16da8e8198
=======
	first_grid.set_flow(100, -100);
	first_grid.set_circle(50,50,20,0);

	Finite_Difference fd (first_grid);
	fd.set_precision(0.01);
>>>>>>> 78b591d74860275455bd0cf338ba35d685a6175d
	fd.set_maxit(10000);
	Grid sol = fd.get_solution();
	//cout << fd.get_iterations() << endl;
	sol.efield();
<<<<<<< HEAD
	sol.print_gnuplot_values();
	sol.print_matrix_to("matrix_circle_fd.dat");
	sol.print_all_to("all_circle_fd.dat");
	
=======
//	sol.print_gnuplot_values();
//	sol.print_matrix_to("matrix_circle_fd.dat");
	sol.print_all_to("all_circle_fd.dat");

	Gnuplot gp(sol);
	gp.add_comment("testing comment");
	gp.add_command("set term jpeg");
	gp.add_command("set output 'test.jpg'");
	gp.add_plot();
	gp.save_string("foo.gnu");
	gp.sendString();

	Gnuplot rf(sol);
	rf.read_file("foo.gnu");
	rf.save_string("bar.gnu");

>>>>>>> 78b591d74860275455bd0cf338ba35d685a6175d
	return 0;

	}
