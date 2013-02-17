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

private:
	FILE *fp;
	std::string str;
	std::stringstream strStream;

};

#endif /* GNUPLOT_H_ */
