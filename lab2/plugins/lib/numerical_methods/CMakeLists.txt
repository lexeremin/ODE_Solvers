cmake_minimum_required(VERSION 3.15)

project(numerical_methods)

add_library(euler_method SHARED euler_method/eulerMethod.cpp)
add_library(runge-kutta_method SHARED runge-kutta_method/rungekuttaMethod.cpp)
add_library(heun_method SHARED heun_method/heunMethod.cpp)
add_library(adams-bashforth_method SHARED adams_bashforth_method/adamsbashforthMethod.cpp)
#add_library(plot SHARED ../plot_tools/plot.cpp ../plot_tools/plot.h)