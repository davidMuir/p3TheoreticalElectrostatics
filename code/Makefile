finite_difference: finite_difference.o ./include/grid.h
	g++ -std=c++11 -o finite_difference finite_difference.o
	
finite_difference.o: finite_difference.cc include/finite_difference.h
	g++ -std=c++11 -c finite_difference.cc
	
./include/grid.o: ./include/grid.h
	g++ -std=c++11 -c ./include/grid.h
	
clean:
	rm finite_difference.o ./Structures/*.o ./Algorithms/*.o
