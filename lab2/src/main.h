//
// Created by Seeksub on 15.11.2019.
//

#ifndef LAB1_MAIN_H
#define LAB1_MAIN_H

#include <vector>
#include <cmath>
#include <string>
#include <iostream>
#include <fstream>
#include <ctime>
#include <regex>

#include <dlfcn.h>
#include <dirent.h>

#include "../plugins/interfaceBasedPlugin.h"
#include "../plugins/interfaceNumMethodPlugin.h"
#include "../plugins/interfaceVisualizerPlugin.h"

using namespace std;

typedef ifc_BasePlugin* RegisterPlugin();

//class inputData {
//private:
//    double h = 0.0;
//    double m = 0.0;
//    double g = 0.0;
//    double alpha = 0.0;
//    double simTime = 0.0;
//public:
//    inputData(double _h, double _m, double _g, double _alpha, double _simTime):
//            h(_h), m(_m), g(_g), alpha(_alpha), simTime(_simTime){};
//    double getStep() {
//        return this->h;
//    }
//    double getGrav() {
//        return this->g;
//    }
//    double getMass() {
//        return this->m;
//    }
//    double getAlpha() {
//        return this->alpha;
//    }
//    double getSimTime() {
//        return this->simTime;
//    }
//};

//class Normalization {
//private:
//    vector <double> L1;
//    vector <double> L2;
//public:
//    vector <double> getL1() {
//        return this->L1;
//    }
//    vector <double> getL2() {
//        return this->L2;
//    }
//    void addToL1(double _L1) {
//        this->L1.emplace_back(_L1);
//    }
//    void addToL2(double _L2){
//        this->L2.emplace_back(_L2);
//    }
//};

// pair for double vector for x and y values
typedef pair<double, double> Points;
typedef double (dFunc) (double);

typedef vector<Points> P;
typedef vector<P> Solutions;
//making func type that can return double vector
typedef vector<Points> Method(inputData *data, Normalization *Norma, Points p, dFunc *f);

//extern "C" class ifc_BasePlugin;
//extern "C" class ifc_NumericalMethodPlugin;
//extern "C" class ifc_VisualizerPlugin;

#endif //LAB1_MAIN_H
