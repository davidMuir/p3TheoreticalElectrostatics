objects = main.o Grid3d.o Algorithm3d.o Finite_Difference3d.o
CC=g++ -std=c++11

foo : $(objects)
	$(CC) -o foo $(objects)

main.o : main.cc Finite_Difference3d.h
	$(CC) -c main.cc

Grid3d.o : Grid3d.h Grid3d.cc
	$(CC) -c Grid3d.cc

Algorithm3d.o : Algorithm3d.h Algorithm3d.cc
	$(CC) -c Algorithm3d.cc

Finite_Difference3d.o : Finite_Difference3d.h Finite_Difference3d.cc
	$(CC) -c Finite_Difference3d.cc

clean : rm foo $(objects)