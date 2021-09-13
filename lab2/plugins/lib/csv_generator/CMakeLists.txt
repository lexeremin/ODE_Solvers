cmake_minimum_required(VERSION 3.15)

project(csv_generator)

add_library(csv_gen SHARED csvGenerator.cpp csvGenerator.h)
#add_library(runge-kutta_method SHARED runge-kutta_method/rungekuttaMethod.cpp)
#add_library(heun_method SHARED heun_method/heunMethod.cpp)
#add_library(adams-bashforth_method SHARED adams-bashforth_method/adamsbashforthMethod.cpp)
#add_library(plot SHARED ../plot_tools/plot.cpp ../plot_tools/plot.h)