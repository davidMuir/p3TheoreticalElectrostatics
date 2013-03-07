code = ../code/
libname = $(code)theoretical.a
CC = g++ -std=c++11 -Ofast
programs = multiple_conductors integrating_test
export CC

multiple_conductors : multiple_conductors.cc
	$(MAKE) -C $(code); $(CC) -I $(code) multiple_conductors.cc $(libname) -o multiple_conductors

integrating_test : integrating_test.cc
	$(MAKE) -C $(code); $(CC) -I $(code) integrating_test.cc $(libname) -o integrating_test

clean :
	rm $(programs); cd $(code); make clean
