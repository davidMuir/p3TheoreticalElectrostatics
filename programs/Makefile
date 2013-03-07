code = ../code/
libname = $(code)theoretical.a
CC = g++ -std=c++11 -Ofast
programs = multiple_conductors integrating_test eq_lines_on_heatmap_with_figure eqlines animation
export CC

all : $(programs)

multiple_conductors : multiple_conductors.cc
	$(MAKE) -C $(code); $(CC) -I $(code) multiple_conductors.cc $(libname) -o multiple_conductors

integrating_test : integrating_test.cc
	$(MAKE) -C $(code); $(CC) -I $(code) integrating_test.cc $(libname) -o integrating_test

eq_lines_on_heatmap_with_figure : eq_lines_on_heatmap_with_figure.cc
	$(MAKE) -C $(code); $(CC) -I $(code) eq_lines_on_heatmap_with_figure.cc $(libname) -o eq_lines_on_heatmap_with_figure

eqlines : eqlines.cc
	$(MAKE) -C $(code); $(CC) -I $(code) eqlines.cc $(libname) -o eqlines

animation : animation.cc
	$(MAKE) -C $(code); $(CC) -I $(code) animation.cc $(libname) -o animation

clean :
	rm $(programs); cd $(code); make clean
