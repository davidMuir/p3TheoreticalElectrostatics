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
	first_grid.set_conductor(60,25,15,0,triangle);
	Finite_Difference fd (first_grid);
	fd.set_precision(0.00001);
	fd.set_maxit(10000);
	Grid sol_fd = fd.get_solution();

	Gnuplot gp(sol_fd);
	gp.add_comment("testing comment");
	gp.add_command("set term jpeg");
	gp.add_command("set output 'test.jpg'");
	gp.add_command("set xrange [0:100]");
	gp.add_command("set yrange [0:100]");
	gp.add_command("unset key");
	gp.add_command("set cbrange [-50:50]");
	gp.add_command("set palette color");
	gp.add_command("set palette defined");
	gp.add_plot();
	gp.sendString();

	sol_fd.set_conductor(50,75,15,0,circle);

	Finite_Difference fd1 (sol_fd);
	fd1.set_precision(0.00001);
	fd1.set_maxit(10000);
	Grid sol_fd1 = fd1.get_solution();

	Gnuplot gp1(sol_fd1);
	gp1.add_comment("testing comment");
	gp1.add_command("set term jpeg");
	gp1.add_command("set output 'test_second.jpg'");
	gp1.add_command("set xrange [0:100]");
	gp1.add_command("set yrange [0:100]");
	gp1.add_command("unset key");
	gp1.add_command("set cbrange [-50:50]");
	gp1.add_command("set palette color");
	gp1.add_command("set palette defined");
	gp1.add_plot();
	gp1.sendString();
	

	return 0;

	}
