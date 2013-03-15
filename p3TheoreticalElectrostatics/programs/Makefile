code = ../code/
libname = $(code)theoretical.a
CC = g++ -std=c++11 -Ofast
programs = multiple_conductors eqlines animation efield
export CC

all : $(programs)

multiple_conductors : multiple_conductors.cc
	$(MAKE) -C $(code); $(CC) -I $(code) multiple_conductors.cc $(libname) -o multiple_conductors

eqlines : eqlines.cc
	$(MAKE) -C $(code); $(CC) -I $(code) eqlines.cc $(libname) -o eqlines

animation : animation.cc
	$(MAKE) -C $(code); $(CC) -I $(code) animation.cc $(libname) -o animation

efield : efield.cc
	$(MAKE) -C $(code); $(CC) -I $(code) efield.cc $(libname) -o efield

clean :
	rm $(programs); cd $(code); make clean
