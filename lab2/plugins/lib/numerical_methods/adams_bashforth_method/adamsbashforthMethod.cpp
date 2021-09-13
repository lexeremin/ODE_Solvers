//
// Created by Seeksub on 03.10.2019.
//
#include "../numerical_methods.h"
#include "../../../interfaceNumMethodPlugin.h"


class AdamsBashforth : public ifc_NumericalMethodPlugin {
public:
    char* GetPluginName(char* o_name)const{
        strcpy(o_name, "AdamsBashforth");
        return o_name;
    }
    virtual bool isInstanceOf(const char* p_interface_name) const {
        return strcmp(p_interface_name , "AdamsBashforth")==0 ? true: ifc_NumericalMethodPlugin::isInstanceOf(p_interface_name);
    }
    vector<Points>solver(inputData *data, Normalization *Norma, Points p, dFunc *f) {
        vector<Points> rkSolution;
        double y1, y2, y3, y4, y5;
        double yi = p.second, xi = p.first;
        rkSolution.emplace_back(xi, yi);
        while (xi < data->getSimTime()){
            Norma->addToL1(yi);
            Norma->addToL2(yi);
            y1 = yi + data->getStep()*f(yi);
            xi += data->getStep();
            rkSolution.emplace_back(xi, y1);
            Norma->addToL1(y1);
            Norma->addToL2(y1);
            y2 = y1 + data->getStep()*(3/2*f(y1)-1/2*f(yi));
            xi += data->getStep();
            rkSolution.emplace_back(xi, y2);
            Norma->addToL1(y2);
            Norma->addToL2(y2);
            y3 = y2 + data->getStep()*(23/12*f(y3) - 4/3*f(y1) + 5/12*f(yi));
            xi += data->getStep();
            rkSolution.emplace_back(xi, y3);
            Norma->addToL1(y3);
            Norma->addToL2(y3);
            y4 = y3 + data->getStep()*(55/24*f(y3) - 59/24*f(y2) + 37/24*f(y1) - 3/8*f(yi));
            xi += data->getStep();
            rkSolution.emplace_back(xi, y4);
            Norma->addToL1(y4);
            Norma->addToL2(y4);
            y5 = y4 + data->getStep() * (1901/720*f(y4) - 1387/360*f(y3) +
                                109/30*f(y2) - 637/360*(y1) + 251/720*f(yi));
            xi += data->getStep();
            rkSolution.emplace_back(xi, y5);
            yi  = y5;
        }
        return rkSolution;
    }
};

extern "C" ifc_BasePlugin* registerPlugin() {
    return new AdamsBashforth();
}
