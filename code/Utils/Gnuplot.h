/*
 * Gnuplot.h
 *
 *  Created on: 17 Feb 2013
 *      Author: david
 */

#ifndef GNUPLOT_H_
#define GNUPLOT_H_

#include "../Structures/Grid.h"
#include <iostream>
#include <sstream>
#include "../Utils/Utils.h"

#define GNUPLOT "/usr/bin/gnuplot"

class Gnuplot {
public:
	Gnuplot(Grid entry);
	virtual ~Gnuplot();
	void add_command(std::string command);
	void add_comment(std::string comment);
	void save_string(std::string output);
	void sendString();
	void read_file(std::string input);
	void add_plot();

private:
	FILE *fp;
	std::string str;
	std::string data;
	std::stringstream strStream;
	std::stringstream datStream;
	std::string numberToString(int Number);
    std::string numberToString(double Number);
};

#endif /* GNUPLOT_H_ */
