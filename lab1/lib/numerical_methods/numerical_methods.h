//
// Created by Seeksub on 03.10.2019.
//

#ifndef LAB1_NUMERICAL_METHODS_H
#define LAB1_NUMERICAL_METHODS_H

#include <vector>
#include <cmath>
using namespace std;

class inputData {
private:
    double h = 0.0;
    double m = 0.0;
    double g = 0.0;
    double alpha = 0.0;
    double simTime = 0.0;
//    vector <double> L1;
//    vector <double> L2;
public:
    inputData(double _h, double _m, double _g, double _alpha, double _simTime):
        h(_h), m(_m), g(_g), alpha(_alpha), simTime(_simTime){};
    double getStep() {
        return this->h;
    }
    double getGrav() {
        return this->g;
    }
    double getMass() {
        return this->m;
    }
    double getAlpha() {
        return this->alpha;
    }
    double getSimTime() {
        return this->simTime;
    }
//   vector <double> getL1() {
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
//    void sqrtL2(){
//        this->L2 = sqrt(this->L2);
//    }
//    void setLtoNull() {
//        clear(this->L1);
//        clear(this->L2);
//    }
};

class Normalization {
private:
    vector <double> L1;
    vector <double> L2;
public:
    vector <double> getL1() {
        return this->L1;
    }
    vector <double> getL2() {
        return this->L2;
    }
    void addToL1(double _L1) {
        this->L1.emplace_back(_L1);
    }
    void addToL2(double _L2){
        this->L2.emplace_back(_L2);
    }
};

// pair for double vector for x and y values
typedef pair<double, double> Points;
typedef double (dFunc) (double);
//making func type that can return double vector
typedef vector<Points> Method(inputData *data, Normalization *Norma, Points p, dFunc *f);


extern "C" vector<Points> euler(inputData *data, Normalization *Norma, Points p, dFunc *f);
extern "C" vector<Points> rungekutta(inputData *data, Normalization *Norma, Points p, dFunc *f);
//double h, double simTime,
#endif //LAB1_NUMERICAL_METHODS_H
