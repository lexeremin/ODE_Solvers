//
// Created by Seeksub on 03.10.2019.
//
#include "plot.h"

void plot(string file_name) {
#ifdef WIN32
    FILE *pipe = _popen(GNUPLOT_NAME, "w");
#else
    FILE *pipe = popen(GNUPLOT_NAME, "w");
#endif
    if(pipe != NULL) {
        fprintf(pipe,"set tics font ',12'\n "
                     "set key on bottom\n"
                     "set key font ',14'\n "
                     "set xlabel 't' font ',14'\n "
                     "set ylabel 'v(t)' font ',14'\n "
                     "plot '%s' using 1:2 w lp title 'Euler', "
                     "'' using 1:3 w lp title 'Runge-Kutta', "
                     "'' using 1:4 w lp title 'Analytical'\n"
                ,file_name.c_str());

//        "'' using 1:5 w lp title 'A - E', "
//        "'' using 1:6 w lp title 'A - RK'\n"
#ifdef WIN32
        _pclose(pipe);
#else
        pclose(pipe);
#endif
    } else{
        cout<<"Couldn't open pipe" << endl;
    }
}

void plotNorma(string file_name) {
#ifdef WIN32
    FILE *pipe = _popen(GNUPLOT_NAME, "w");
#else
    FILE *pipe = popen(GNUPLOT_NAME, "w");
#endif
    if(pipe != NULL) {
        fprintf(pipe,
                "set tics font ',12'\n "
                "set key font ',14'\n "
                "set xlabel 'step' font ',14'\n "
                "set ylabel 'L' font ',14'\n "
                "plot '%s' using 1:2 w lp title 'Euler L2', "
                     "'' using 1:3 w lp title 'Runge-Kutta L2'\n"
                ,file_name.c_str());

#ifdef WIN32
        _pclose(pipe);
#else
        pclose(pipe);
#endif
    } else{
        cout<<"Couldn't open pipe" << endl;
    }
}
