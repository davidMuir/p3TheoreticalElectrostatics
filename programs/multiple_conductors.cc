#include "Algorithms/Asymmetric_Finite_Volume.h"
#include "Utils/Gnuplot.h"
#include "Algorithms/Finite_Difference.h"
#include "Algorithms/Fast_Finite_Difference.h"
#include "Errors/Compare.h"
#include "Utils/Conductors.h"
#include "Utils/Utils.h"

using namespace std;

int main() {

	int n = 200;
	int m = 200;

	Grid first_grid(n,m);

	first_grid.set_flow(50, -50);

	cout << "Integrated field before conductors: " << sum_grid(first_grid) << endl;

    first_grid.set_conductor(150, 130, 40, 70, random_shape, 50, 90, 120, 100, 140, 150);

	//first_grid.set_conductor(150,130,40,50,star);
	//first_grid.set_conductor(50,70,15,0,circle);

	Finite_Difference fd (first_grid);
	fd.set_precision(0);
	fd.set_maxit(10000);
	Grid sol_fd = fd.get_solution();

	cout << "Integrated field after one conductor: " << sum_grid(sol_fd) << endl;

	Gnuplot gp(sol_fd);
	gp.add_comment("testing comment");
	gp.add_command("set term jpeg");
	gp.add_command("set output 'test.jpg'");
	gp.add_command("set xrange [0:200]");
	gp.add_command("set yrange [0:200]");
	gp.add_command("unset key");
	gp.add_command("set cbrange [-50:50]");
	gp.add_command("set palette color");
	gp.add_command("set palette defined");
	gp.add_plot();
	gp.sendString();

	sol_fd.set_conductor(50,70,40,0,circle);
	//sol_fd.set_conductor(150,130,15,0,circle);

	Finite_Difference fd1 (sol_fd);
	fd1.set_precision(0);
	fd1.set_maxit(10000);
	Grid sol_fd1 = fd1.get_solution();

	Gnuplot gp1(sol_fd1);
	gp1.add_comment("testing comment");
	gp1.add_command("set term jpeg");
	gp1.add_command("set output 'test_second.jpg'");
	gp1.add_command("set xrange [0:200]");
	gp1.add_command("set yrange [0:200]");
	gp1.add_command("unset key");
	gp1.add_command("set cbrange [-50:50]");
	gp1.add_command("set palette color");
	gp1.add_command("set palette defined");
	gp1.add_plot();
	gp1.sendString();

	Conductors conductors(n,m,50.,-50.);
	conductors.new_conductor(150,130,40,0,circle);
	conductors.new_conductor(50,70,40,0,circle);
	conductors.set_precision(0);
	conductors.set_maxit(10000);
	Grid sol_new = conductors.get_solution(FD);

	Gnuplot gp2(sol_new);
	gp2.add_comment("testing comment");
	gp2.add_command("set term jpeg");
	gp2.add_command("set output 'test_new.jpg'");
	gp2.add_command("set xrange [0:200]");
	gp2.add_command("set yrange [0:200]");
	gp2.add_command("unset key");
	gp2.add_command("set cbrange [-50:50]");
	gp2.add_command("set palette color");
	gp2.add_command("set palette defined");
	gp2.add_plot();
	gp2.sendString();

	Grid diff = find_err(sol_fd1, sol_new);

	Gnuplot gp3(diff);
	gp3.add_comment("testing comment");
	gp3.add_command("set term jpeg");
	gp3.add_command("set output 'test_diff.jpg'");
	gp3.add_command("set xrange [0:200]");
	gp3.add_command("set yrange [0:200]");
	gp3.add_command("unset key");
	gp3.add_command("set cbrange [-5:5]");
	gp3.add_command("set palette color");
	gp3.add_command("set palette defined");
	gp3.add_plot();
	gp3.sendString();

	cout << "Integrated field in old method: " << sum_grid(sol_fd1) << endl;
	cout << "Integrated field in new method: " << sum_grid(sol_new) << endl;

	Analytic analytic(first_grid);
	analytic.solve(50,50,20,0,1);
	Grid ana = analytic.get_solution();

	cout << "Integrated field in analytic method: " << sum_grid(ana) << endl;


	return 0;

	}
