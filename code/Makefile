objects = main.o ./Structures/Grid.o ./Algorithms/Finite_Difference.o ./Algorithms/Algorithm.o
CC = g++ -std=c++11
					
foo : $(objects)
	$(CC) -o foo $(objects)
	
main.o : main.cc ./Algorithms/Finite_Difference.h
	$(CC) -c main.cc
	
./Algorithms/Finite_Difference.o : ./Algorithms/Finite_Difference.cc ./Algorithms/Finite_Difference.h
	cd ./Algorithms; $(CC) -c Finite_Difference.cc
	
./Algorithms/Algorithm.o : ./Algorithms/Algorithm.h ./Algorithms/Algorithm.cc
	cd ./Algorithms;$(CC) -c Algorithm.cc
	
./Structures/Grid.o : ./Structures/Grid.h ./Structures/Grid.cc
	cd ./Structures; $(CC) -c Grid.cc
	
clean :
	rm foo $(objects)