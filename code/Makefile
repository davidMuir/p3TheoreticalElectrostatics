objects = ./Structures/Grid.o ./Algorithms/Finite_Difference.o ./Algorithms/Fast_Finite_Difference.o ./Algorithms/Asymmetric_Finite_Volume.o ./Algorithms/Algorithm.o ./Utils/Gnuplot.o
libname = theoretical.a
CC = g++ -std=c++11 -Ofast
	
all : $(libname)
	
$(libname) : $(objects)
	ar rvs $(libname) $(objects)
	
./Algorithms/Finite_Difference.o : ./Algorithms/Finite_Difference.h ./Algorithms/Finite_Difference.cc
	cd ./Algorithms; $(CC) -c Finite_Difference.cc

./Algorithms/Fast_Finite_Difference.o : ./Algorithms/Fast_Finite_Difference.h ./Algorithms/Fast_Finite_Difference.cpp
	cd ./Algorithms; $(CC) -c Fast_Finite_Difference.cpp

./Algorithms/Asymmetric_Finite_Volume.o : ./Algorithms/Asymmetric_Finite_Volume.h ./Algorithms/Asymmetric_Finite_Volume.cc
	cd ./Algorithms; $(CC) -c Asymmetric_Finite_Volume.cc

./Algorithms/Algorithm.o : ./Algorithms/Algorithm.h ./Algorithms/Algorithm.cc
	cd ./Algorithms; $(CC) -c Algorithm.cc
	
./Structures/Grid.o : ./Structures/Grid.h ./Structures/Grid.cc
	cd ./Structures; $(CC) -c Grid.cc
	
./Utils/Gnuplot.o : ./Utils/Gnuplot.h ./Utils/Gnuplot.cpp
	cd ./Utils/; $(CC) -c Gnuplot.cpp
	
clean :
	rm $(objects) $(libname) 

.PHONY: all clean