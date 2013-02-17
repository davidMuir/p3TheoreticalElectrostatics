#include "Algorithms/Asymmetric_Finite_Volume.h"
#include "Utils/Gnuplot.h"
#include "Algorithms/Finite_Difference.h"

using namespace std;

int main() {
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

	Gnuplot gp(sol);
	gp.add_comment("testing comment");
	gp.add_command("set term jpeg");
	gp.add_command("set output 'test.jpg'");
	gp.add_command("p 'matrix_circle_fd.dat' w l");
	gp.save_string("foo.gnu");
	gp.sendString();

	Gnuplot rf(sol);
	rf.read_file("foo.gnu");
	rf.save_string("bar.gnu");

	return 0;

	}
