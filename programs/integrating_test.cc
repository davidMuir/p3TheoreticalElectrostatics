#include "Algorithms/Asymmetric_Finite_Volume.h"
#include "Utils/Gnuplot.h"
#include "Algorithms/Finite_Difference.h"
#include "Algorithms/Fast_Finite_Difference.h"
#include "Errors/Compare.h"
#include "Utils/Conductors.h"
#include "Utils/Utils.h"

int main() {

	int n = 200;
	int m = 200;

    Grid test(n,m);

    test.set_flow(1000,-1000);
    test.set_conductor(100,100,5,0,circle);


	Asymmetric_Finite_Volume fd (test);
	fd.set_precision(0);
	fd.set_maxit(20000);
	Grid sol_fd = fd.get_solution();

    cout << "Integrated field: " << sum_grid(sol_fd) << endl;

    Gnuplot gp(sol_fd);
	gp.add_command("set term jpeg");
	gp.add_command("set output 'field_test.jpg'");
	gp.add_command("unset key");
	gp.add_command("set palette color");
	gp.add_command("set palette defined");
	gp.add_plot();
	gp.sendString();


	Grid ana(n,m);
	ana.set_flow(1000,-1000);

    Analytic an(ana);
    an.solve(100,100,5,0,1);
    Grid ana2 = an.get_solution();

    cout << "Integrated analytic field: " << sum_grid(ana2) << endl;

    Gnuplot gp1(ana2);
	gp1.add_command("set term jpeg");
	gp1.add_command("set output 'field_analytic.jpg'");
	gp1.add_command("unset key");
	gp1.add_command("set palette color");
	gp1.add_command("set palette defined");
	gp1.add_plot();
	gp1.sendString();

    Grid error = find_err_relative(sol_fd,ana2);

    Gnuplot gp3(error);
	gp3.add_command("set term jpeg");
	gp3.add_command("set output 'field_error.jpg'");
	gp3.add_command("unset key");
	gp3.add_command("set palette color");
	gp3.add_command("set palette defined");
	gp3.add_plot();
	gp3.sendString();


    return 0;

}

