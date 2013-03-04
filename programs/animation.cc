#include "../code/Algorithms/Asymmetric_Finite_Volume.h"
#include "../code/Utils/Gnuplot.h"
#include "../code/Algorithms/Finite_Difference.h"
#include "../code/Algorithms/Fast_Finite_Difference.h"
#include "../code/Errors/Compare.h"
#include "../code/Utils/Animation.h"
#include "../code/Utils/Conductors.h"
#include "../code/Structures/Grid.h"
#include <ctime>

using namespace std;


int main() {

	int N = 17;   // number of eq.p. lines
	int n = 100;
	int m = 100;

	double Emax=100;
	double Emin=-100;

	Grid first_grid(n,m);

	first_grid.set_flow(Emax, Emin);
	first_grid.set_boundary_shape(50,50,20,0,0,circle);
	first_grid.print_figure_to("figure.dat", 1);

	Animation anim(first_grid);
//	anim.set_lines(1, white, N); // 0 - if you dont need eq.p lines. possible colors: black, white, green, blue, violet, red
//	anim.set_figure(1, violet);  // same here
//	anim.set_iterations(4000);
//	anim.set_time(10.0); // for which your animation will run, in seconds
//	anim.set_precision(0.00001);
//	anim.set_heatmap(0); // 0 - if you dont need heatmap on the background 
//	anim.set_algorithm(FFD); // possible: FD, FFD, AFV, though Works only for FFD :/ 
	anim.create_data(); 
	anim.animate();
	anim.delete_data();
}

