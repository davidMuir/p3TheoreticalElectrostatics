code = ../code/
libname = $(code)theoretical.a
CC = g++ -std=c++11 -Ofast
main = multiple_conductors.cc
program = multiple_conductors

all : $(libname)
	$(CC) -I $(code) $(main) $(libname) -o $(program)
	
$(libname) : ../code/Makefile
	cd $(code); make
	
clean : 
	rm $(program); cd $(code); make clean
