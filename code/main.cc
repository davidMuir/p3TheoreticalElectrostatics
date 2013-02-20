#include "Algorithms/Asymmetric_Finite_Volume.h"
#include "Utils/Gnuplot.h"
#include "Algorithms/Finite_Difference.h"

using namespace std;

int main() {

	int n = 100;
	int m = 100;

	Grid first_grid(n,m);

	first_grid.set_flow(50, -50);
	first_grid.set_boundary_shape(25,25,10,0,0,circle);

	Finite_Difference fd (first_grid);
	fd.set_precision(0.00001);
	fd.set_maxit(10000);

	Grid shape = first_grid.get_boundary_grid(50,50,25,25,10,0,circle);
	
//	sol.print_gnuplot_values();
//	sol.print_matrix_to("matrix_circle_fd.dat");

	Gnuplot gp(shape);
	gp.add_comment("testing comment");
	gp.add_command("set term jpeg");
	gp.add_command("set output 'test.jpg'");
	gp.add_command("set xrange [0:50]");
	gp.add_command("set yrange [0:50]");
	gp.add_command("unset key");
	gp.add_command("set cbrange [-50:50]");
	gp.add_command("set palette color");
	gp.add_command("set palette defined");
	gp.add_plot();
	gp.save_string("foo.gnu");
	gp.sendString();
	
	return 0;

	}
