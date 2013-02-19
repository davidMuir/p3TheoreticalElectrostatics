objects = main.o ./Structures/Grid.o ./Algorithms/Finite_Difference.o ./Algorithms/Asymmetric_Finite_Volume.o ./Algorithms/Algorithm.o ./Utils/Gnuplot.o
CC = g++ -std=c++11

all : $(objects)
	$(CC) -o foo $(objects)
	
main.o : main.cc ./Algorithms/Finite_Difference.h
	$(CC) -c main.cc
	
./Algorithms/Finite_Difference.o : ./Algorithms/Finite_Difference.h ./Algorithms/Finite_Difference.cc
	cd ./Algorithms; $(CC) -c Finite_Difference.cc

./Algorithms/Asymmetric_Finite_Volume.o : ./Algorithms/Asymmetric_Finite_Volume.h ./Algorithms/Asymmetric_Finite_Volume.cc
	cd ./Algorithms; $(CC) -c Asymmetric_Finite_Volume.cc
	
./Algorithms/Algorithm.o : ./Algorithms/Algorithm.h ./Algorithms/Algorithm.cc
	cd ./Algorithms; $(CC) -c Algorithm.cc
	
./Structures/Grid.o : ./Structures/Grid.h ./Structures/Grid.cc
	cd ./Structures; $(CC) -c Grid.cc
	
./Utils/Gnuplot.o : ./Utils/Gnuplot.h ./Utils/Gnuplot.cpp
	cd ./Utils/; $(CC) -c Gnuplot.cpp
	
clean :
	rm foo $(objects)
