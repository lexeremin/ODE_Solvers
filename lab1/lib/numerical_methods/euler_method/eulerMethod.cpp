//
// Created by Seeksub on 03.10.2019.
//
#include "../numerical_methods.h"

//euler method solution
vector<Points> euler(inputData *data, Normalization *Norma, Points p, dFunc *f) {
    vector<Points> eSolution;
    double y;
    double yi = p.second, xi = p.first;
    eSolution.emplace_back(xi, yi);
    while(xi < data->getSimTime()){
        Norma->addToL1(yi);
        Norma->addToL2(yi);
        y = yi + data->getStep() * f(yi);
        xi += data->getStep();
        eSolution.emplace_back(xi, y);
        yi = y;
    }
    return eSolution;
}



