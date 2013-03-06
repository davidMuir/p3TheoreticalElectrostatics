code = ../code/
libname = $(code)theoretical.a
CC = g++ -std=c++11 -Ofast
main = multiple_conductors.cc
program = multiple_conductors

all :
	$(MAKE) -C $(code); $(CC) -I $(code) $(main) $(libname) -o $(program)
	
clean : 
	rm $(program); cd $(code); make clean
