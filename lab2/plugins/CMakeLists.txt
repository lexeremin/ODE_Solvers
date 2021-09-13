cmake_minimum_required(VERSION 3.15)

project(numerical_methods)

add_subdirectory(lib/numerical_methods/)
add_subdirectory(lib/csv_generator)
add_subdirectory(lib/plot_tools)
add_library(ifc_base SHARED interfaceBasedPlugin.h interfaceBasedPlugin.cpp)
add_library(ifc_visualizer SHARED interfaceVisualizerPlugin.h interfaceVisualizerPlugin.cpp)
add_library(ifc_num_methods SHARED interfaceNumMethodPlugin.h interfaceNumMethodPlugin.cpp)

#add_library(plot SHARED ../plot_tools/plot.cpp ../plot_tools/plot.h)