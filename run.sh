#!/bin/bash

#Files to be used
PROGRAM="foo"
DATA_FILE="results_new.dat"
GNUPLOT_SCRIPT="asym.gnu"

#Make sure not to overwrite and check availability
if [ -e ./data/$DATA_FILE ] 
	then
	echo "$DATA_FILE exists. Terminating."
	exit 1
	fi

if [ ! -e ./code/$PROGRAM ] 
	then
	echo "$PROGRAM does not exist. Terminating."
	exit 1
	fi

if [ ! -e ./data/$GNUPLOT_SCRIPT ] 
	then
	echo "$GNUPLOT_SCRIPT does not exist. Terminating."
	exit 1
	fi

./code/$PROGRAM > ./data/$DATA_FILE
gnuplot ./data/$GNUPLOT_SCRIPT
exit 0
