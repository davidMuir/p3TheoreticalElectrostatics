/*
 * Gnuplot.cpp
 *
 *  Created on: 17 Feb 2013
 *      Author: david
 */

#include "Gnuplot.h"

Gnuplot::Gnuplot(Grid entry) {
	fp = popen(GNUPLOT, "w");
	str = strStream.str();
}

Gnuplot::~Gnuplot() {
	pclose(fp);
}

void Gnuplot::sendString() {
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
