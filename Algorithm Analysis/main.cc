#include "Algorithms/Asymmetric_Finite_Volume.h"
#include "Utils/Gnuplot.h"
#include "Utils/BmpReader.h"
#include "Algorithms/Finite_Difference.h"
#include "Algorithms/Fast_Finite_Difference.h"
#include "Errors/Compare.h"
#include <time.h>

int main(int argc,char *argv[]) {

#define LIMIT 10000

//	int n = atoi(argv[1]);
//	int m = n;
//	timespec t0, t1, t2, t3;
//
//	Grid g1(n,m),g2(n,m),g3(n,m);
//	g1.set_flow(-50,50);
//	g2.set_flow(-50,50);
//	g3.set_flow(-50,50);
//	g1.set_conductor(n/2,m/2,n/10, 0, circle);
//	g2.set_conductor(n/2,m/2,n/10, 0, circle);
//	g3.set_conductor(n/2,m/2,n/10, 0, circle);
//
//	Finite_Difference fd(g1);
//	Fast_Finite_Difference ffd(g2);
//	Asymmetric_Finite_Volume afv(g3);
//	fd.set_precision(0.000001);
//	ffd.set_precision(0.000001);
//	afv.set_precision(0.000001);
//	fd.set_maxit(LIMIT);
//	ffd.set_maxit(LIMIT);
//	afv.set_maxit(LIMIT);
//	clock_gettime(CLOCK_REALTIME,&t0);
//	fd.get_solution();
//	clock_gettime(CLOCK_REALTIME,&t1);
//	ffd.get_solution();
//	clock_gettime(CLOCK_REALTIME,&t2);
//	afv.get_solution();
//	clock_gettime(CLOCK_REALTIME,&t3);
//
//	std::cout << difftime(t1.tv_sec,t0.tv_sec) << "\t" << difftime(t2.tv_sec,t1.tv_sec) << "\t" << difftime(t3.tv_sec,t2.tv_sec) << std::endl;

//	Grid g1(n,m),g2(n,m);
//	g1.set_flow(-50,50);
//	g2.set_flow(-50,50);
//	g1.set_conductor(n/2,m/2,n/10, 0, circle);
//	g2.set_conductor(n/2,m/2,n/10, 0, circle);
//	Finite_Difference fd(g1);
//	Fast_Finite_Difference ffd(g2);
//	fd.set_precision(0);
//	ffd.set_precision(0);
//	fd.set_maxit(LIMIT);
//	ffd.set_maxit(LIMIT);
//    fd.get_solution();
//    ffd.get_solution();
/*
	Gnuplot gp1(fd.get_solution());
	gp1.add_command("set term postscript");
	gp1.add_command("set ytics ('200' 200)");
    gp1.add_command("set xtics ('200' 200)");
	gp1.add_command("set output 'fd.ps'");
	gp1.add_command("set title 'Finite Difference");
	gp1.add_command("unset key");
	gp1.add_command("set palette color");
	gp1.add_command("set palette defined");
	gp1.add_plot();
	gp1.sendString();
	Gnuplot gp2(ffd.get_solution());
	gp2.add_command("set term postscript");
	gp2.add_command("set ytics ('1000' 1000)");
    gp2.add_command("set xtics ('1000' 1000)");
	gp2.add_command("set output 'ffd.ps'");
	gp2.add_command("set title 'Fast Finite Difference");
	gp2.add_command("unset key");
	gp2.add_command("set palette color");
	gp2.add_command("set palette defined");
	gp2.add_plot();
	gp2.sendString();

*/

	double Emax=50;
	double Emin=-50;

	Grid first_grid = Bmp_Reader("Img/fork.bmp").get_grid(boundary,-50,50,0);
	first_grid.print_figure_to("figure.dat", 1);


	Fast_Finite_Difference fd (first_grid);
	fd.set_precision(0.00001);
	fd.set_maxit(10000);
    Grid sol = fd.get_solution();
	sol.print_all_to("results.dat");


	Gnuplot gp(sol);
//	sol.equip_values(11,200,200,Emax,1,1);
//	sol.print_contours_to("eq_lines.dat", 11);


	gp.add_command("set term postscript");
    gp.add_command("set ytics ('200' 200)");
    gp.add_command("set xtics ('200' 200)");
	gp.add_command("set output 'first_plot.ps'");
	gp.add_command("set palette defined");
    gp.add_command("unset key");
	gp.add_command("plot 'results.dat' with image,'figure.dat' with lines ls -1"); // white = ls -3; black = ls -1; red = ls 1; green = 2; blue = ls 3; violet = ls 4;
	gp.sendString();

	return 0;
}
