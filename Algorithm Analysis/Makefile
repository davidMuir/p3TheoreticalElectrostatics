code = ../code/
libname = $(code)theoretical.a
CC = g++ -std=c++11 -Ofast -pg
main = main.cc
program = foo
export CC

all :
	$(MAKE) -C $(code); $(CC) -I $(code) $(main) $(libname) -lrt -o $(program)

clean : 
	rm $(program); $(MAKE) -C $(code) clean
