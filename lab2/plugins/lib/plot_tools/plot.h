//
// Created by Seeksub on 03.10.2019.
//

#ifndef LAB1_PLOT_H
#define LAB1_PLOT_H

#include <iostream>
#include <fstream>
#include <cstdio>
#include "../../interfaceVisualizerPlugin.h"
using namespace std;


//extern "C" void plotSolution(string file_name);
//extern "C" void plotNormalization(string file_name);

#ifdef  WIN32
#define GNUPLOT_NAME "pgnuplot -persist"
#else
    #define GNUPLOT_NAME "gnuplot -persist"
#endif

#endif //LAB1_PLOT_H
