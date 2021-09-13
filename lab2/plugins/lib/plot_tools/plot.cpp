//
// Created by Seeksub on 03.10.2019.
//
#include "plot.h"


class Plot : public ifc_VisualizerPlugin {

    virtual char* GetPluginName(char* o_name)const{
        strcpy(o_name, "Plot");
        return o_name;
    }
    void plotSolution(string file_name) {
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
                     "plot '%s' using 1:2 w lp title 'Runge-Kutta', "
                     "'' using 1:3 w lp title 'Euler', "
                     "'' using 1:4 w lp title 'Adams-Bashforth', "
                     "'' using 1:5 w lp title 'Heun', "
                     "'' using 1:6 w lp title 'Analytical'\n"
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
    void plotNormalization(string file_name) {
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
                    "'' using 1:3 w lp title 'Runge-Kutta L2',"
                    "'' using 1:4 w lp title 'huen L2',"
                    "'' using 1:5 w lp title 'adams-basforth L2'\n"
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
    void plotter(string fileSolution, string fileNorma){
        plotSolution(fileSolution);
        plotNormalization(fileNorma);
    }
    pair<string, string> csvFile(Solutions sPoints, string csvFile, vector<double>Norma, string csvNorma){
        return make_pair(csvFile, csvNorma);
    }

};

extern "C" ifc_BasePlugin* registerPlugin() {
    return new Plot();
}
