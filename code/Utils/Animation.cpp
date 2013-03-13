
#include "Animation.h"


using namespace std;


void Animation::set_precision(double prec) {
		precision = prec;
	}

void Animation::set_iterations(int it) {
		iterations=it;
	}

void Animation::set_time(double t) {
		time = t;
	}

void Animation::set_algorithm(Algo algo) {
	alg=algo;
	}


void Animation::set_lines(bool a, color b, int c) {
	lines.access =a;
	lines.eq_color=b;
	lines.number_of_lines=c;
	}

void Animation::set_figure(bool a, color b, string c) {
	figure.access =a;
	figure.figure_color=b;
	figure.type=c;
	}
void Animation::set_heatmap(bool a) {
	heatmap = a;
	}

Animation::Animation(Grid input_grid) {
	precision=0.00001;
	iterations=4000;
	time=5.0;
	alg=FFD;
	figure.access = 1;
	figure.figure_color = black;
	figure.type = "filledcurve";
	lines.access = 1;
	lines.eq_color = black;
	lines.number_of_lines = 11;
	heatmap = 1;
	entry = input_grid;
}



void Animation::create_data() {
	int total_frames = 10*time;
	int iterations_per_frame = iterations / total_frames;
	Fast_Finite_Difference sol(entry);
/*	switch (alg) {

		case FD: {
			Finite_Difference = sol(entry);
		}

		case FFD: {
			Fast_Finite_Difference(entry) = sol;
		}

		case AFV: {
			Asymmetric_Finite_Volume sol(entry);
		}
		}*/
	sol.set_precision(precision);
	sol.set_maxit(iterations_per_frame);

	for (int iii=0; iii<total_frames; ++iii)
	{
	stringstream ss;
	ss << "data"<< iii << ".dat";
	string str = ss.str();
	ofstream outdata;
	outdata.open(str.c_str());
	if (outdata.is_open()) {

		if (iii!=0) {entry = sol.get_solution();}
		for (int x = 0; x < entry.get_xmax(); x++) {
				for (int y = 0; y < entry.get_ymax(); y++) {
				outdata << x << "\t" << y << "\t" << entry.get_value(x,y) << endl;
				}
			}
		outdata.close();
		}
	else
		{cout << "unable to open file" << endl;}

	if (lines.access) {
	Grid sol2=entry;
	stringstream bbb;
	bbb << "eq_lines"<< iii << ".dat";
	string str2 = bbb.str();
	sol2.equip_values(lines.number_of_lines,entry.get_xmax()-1,entry.get_ymax()-1,entry.get_value(entry.get_xmax()-1,entry.get_ymax()-1),1,1);
	sol2.print_contours_to(str2, lines.number_of_lines);
	}
	}

	stringstream kk;
	kk << "gnu_animate.gp";
	string str = kk.str();
	ofstream outdata;
	outdata.open(str.c_str());
	if (outdata.is_open()) {

		for (int ii=0; ii<total_frames; ++ii)
		{
			if (heatmap) {
				if (lines.access && figure.access)
					{outdata << "plot 'data" << ii << ".dat' with image title \"" << ii*iterations / 10 /time << " iterations\", 'eq_lines" << ii <<".dat' with lines ls " << lines.eq_color -3 <<" notitle, 'figure.dat' with "<< figure.type <<" ls " << figure.figure_color -3 << " notitle " << endl;}
				else if (figure.access)
					{outdata << "plot 'data" << ii << ".dat' with image title \"" << ii*iterations / 10 /time << " iterations\", 'figure.dat' with "<< figure.type <<" ls " << figure.figure_color -3 << " notitle "  << endl;}
				else if (lines.access)
					{outdata << "plot 'data" << ii << ".dat' with image title \"" << ii*iterations / 10 /time << " iterations\", 'eq_lines" << ii <<".dat' with lines ls " << lines.eq_color -3 << " notitle "  << endl;}
				else
					{outdata << "plot 'data" << ii << ".dat' with image title \"" << ii*iterations / 10 /time << " iterations\"" << endl;}
			}

			else if (lines.access && figure.access)
				{outdata << "plot 'eq_lines" << ii <<".dat' with lines ls " << lines.eq_color -3 <<", 'figure.dat' with "<< figure.type <<" ls " << figure.figure_color -3 << " notitle "  << endl;}
			else if (lines.access)
				{outdata << "plot 'eq_lines" << ii <<".dat' with lines ls " << lines.eq_color -3 << " notitle "  << endl;}

		}
		outdata.close();
	}
	else
		cout << "unable to open file" << endl;
}

void Animation::animate() {
	Gnuplot gp(entry);
	gp.add_command("set term gif animate");
	gp.add_command("set output 'animation.gif'");
	gp.add_command("set palette defined");
	gp.add_command("set key opaque");
	stringstream bbb;
	bbb << "set key at "<< entry.get_xmax()-1 << "," << entry.get_ymax()-1;
	string aaa = bbb.str();
	gp.add_command(aaa.c_str());
	gp.add_command("load 'gnu_animate.gp'");
	gp.sendString();
	}

void Animation::delete_data() {
	int total_frames=10*time;
	remove ( "gnu_animate.gp" );
	for (int iii=0; iii<total_frames; ++iii)
		{
		stringstream ss;
		ss << "data"<< iii << ".dat";
		string str = ss.str();
		remove (str.c_str());
		}
	if (lines.access) {
		for (int iii=0; iii<total_frames; ++iii)
		{
		stringstream ss;
		ss << "eq_lines" << iii << ".dat";
		string str = ss.str();
		remove (str.c_str());
		}
		}
	if (figure.access) {
	remove ("figure.dat");
		}
}


//Animation::~Animation {
//}

