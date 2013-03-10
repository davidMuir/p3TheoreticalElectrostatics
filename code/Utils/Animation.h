#ifndef ANIMATION_H_
#define ANIMATION_H_

#include "Gnuplot.h"
#include "../Structures/Grid.h"
#include "../Algorithms/Asymmetric_Finite_Volume.h"
#include "../Algorithms/Finite_Difference.h"
#include "../Algorithms/Fast_Finite_Difference.h"
#include "../Algorithms/Algorithm.h"
#include "../Utils/Conductors.h"
#include <iostream>
#include <sstream>


using namespace std;

enum color {white, notimportant, black, notimport, red, green, blue, violet};

struct eqlines{
bool access;   // 0 if you dont need eq lines in your animation
int number_of_lines;
color eq_color;
};

struct figure_outline{
bool access;  // 0 if you dont need figure outline
color figure_color;
string type;  // filledcurve / points / lines
};


class Animation {
private:
figure_outline figure;
eqlines lines; 
double precision;
int iterations;
double time;
Algo alg; // FD or FDD or AFV
bool heatmap; // 0 if you dont need heatmap on the background
Grid entry;
public:
Animation(Grid input_grid);
void set_precision(double prec);
void set_iterations(int it);
void set_time(double t);
void set_algorithm(Algo algo);
void set_lines(bool a, color b, int c);
void set_figure(bool a, color b, string c);
void set_heatmap(bool a);
void create_data();
void delete_data();
void animate();

//~Animation();

};

#endif 
