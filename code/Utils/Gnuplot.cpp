/*
 * Gnuplot.cpp
 *
 *  Created on: 17 Feb 2013
 *      Author: david
 */

#include "Gnuplot.h"

Gnuplot::Gnuplot(Grid entry) {
	matrix vals = entry.get_values();
	fp = popen(GNUPLOT, "w");
	str = strStream.str();
	for (unsigned int y = 0; y < vals[0].size(); y++) {
		for (unsigned int x = 0; x < vals.size(); x++) {
			 datStream << vals[x][y].value << "	";
		}
		datStream << "\n";
	}
    data = datStream.str();
    int x_siz = vals.size() - 1;
    int y_siz = vals[0].size() - 1;
    double min = lowest_value(vals);
    double max = highest_value(vals);
    std::string s1 = std::string("set xrange [0:") + numberToString(x_siz) + std::string("]");
	add_command(s1);
	std::string s2 = std::string("set yrange [0:") + numberToString(y_siz) + std::string("]");
    add_command(s2);
    std::string s3 = std::string("set cbrange [") + numberToString(min) + std::string(":") + numberToString(max) + std::string("]");
    add_command(s3);

}

Gnuplot::~Gnuplot() {
	pclose(fp);
}

void Gnuplot::sendString() {
	str = strStream.str();
	fprintf(fp,"%s",str.c_str());
}

void Gnuplot::add_command(std::string command) {
	strStream << "\n" << command;
}

void Gnuplot::add_comment(std::string comment) {
	strStream << "\n#" << comment;
}

void Gnuplot::save_string(std::string output) {
	std::ofstream outStream(output.c_str());
	str = strStream.str();
	outStream << str;
}

void Gnuplot::read_file(std::string input) {
	std::ifstream inStream(input.c_str());
	std::string line;
	while (!inStream.eof()) {
		getline(inStream,line);
		add_command(line);
	}
	inStream.close();
}

void Gnuplot::add_plot() {
	strStream << "\np '-' matrix with image #\n" << data;
}

std::string Gnuplot::numberToString (int Number) {
    std::ostringstream ss;
    ss << Number;
    return ss.str();
}

std::string Gnuplot::numberToString (double Number) {
    std::ostringstream ss;
    ss << Number;
    return ss.str();
}

