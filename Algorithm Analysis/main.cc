#include "Algorithms/Asymmetric_Finite_Volume.h"
#include "Utils/Gnuplot.h"
#include "Utils/BmpReader.h"
#include "Algorithms/Finite_Difference.h"
#include "Algorithms/Fast_Finite_Difference.h"
#include "Errors/Compare.h"
#include <time.h>

int main(int argc,char *argv[]) {

#define LIMIT 10000

	int n = atoi(argv[1]);
	int m = n;
	timespec t0, t1, t2, t3;

	Grid g1(n,m),g2(n,m),g3(n,m);
	g1.set_flow(-50,50);
	g2.set_flow(-50,50);
	g3.set_flow(-50,50);
	g1.set_conductor(n/2,m/2,n/10, 0, circle);
	g2.set_conductor(n/2,m/2,n/10, 0, circle);
	g3.set_conductor(n/2,m/2,n/10, 0, circle);

	Finite_Difference fd(g1);
	Fast_Finite_Difference ffd(g2);
	Asymmetric_Finite_Volume afv(g3);
	fd.set_precision(0.000001);
	ffd.set_precision(0.000001);
	afv.set_precision(0.000001);
	fd.set_maxit(LIMIT);
	ffd.set_maxit(LIMIT);
	afv.set_maxit(LIMIT);
	clock_gettime(CLOCK_REALTIME,&t0);
	fd.get_solution();
	clock_gettime(CLOCK_REALTIME,&t1);
	ffd.get_solution();
	clock_gettime(CLOCK_REALTIME,&t2);
	afv.get_solution();
	clock_gettime(CLOCK_REALTIME,&t3);

	std::cout << difftime(t1.tv_sec,t0.tv_sec) << "\t" << difftime(t2.tv_sec,t1.tv_sec) << "\t" << difftime(t3.tv_sec,t2.tv_sec) << std::endl;
	return 0;
}
