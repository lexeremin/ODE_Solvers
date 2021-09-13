//
// Created by Seeksub on 03.10.2019.
//
#include "../numerical_methods.h"
#include "../../../interfaceNumMethodPlugin.h"


class RungeKutta : public ifc_NumericalMethodPlugin {
public:
    char* GetPluginName(char* o_name)const{
        strcpy(o_name, "RungeKutta");
        return o_name;
    }
    virtual bool isInstanceOf(const char* p_interface_name) const {
        return strcmp(p_interface_name , "RungeKutta")==0 ? true: ifc_NumericalMethodPlugin::isInstanceOf(p_interface_name);
    }
    vector<Points> solver(inputData *data, Normalization *Norma, Points p, dFunc *f) {
        vector<Points> rkSolution;
        double y, k1, k2, k3, k4;
        double yi = p.second, xi = p.first;
        rkSolution.emplace_back(xi, yi);
        while (xi < data->getSimTime()){
            Norma->addToL1(yi);
            Norma->addToL2(yi);
            k1 = f(yi);
            k2 = f(yi + data->getStep()/2 * k1);
            k3 = f(yi + data->getStep()/2 * k2);
            k4 = f(yi + data->getStep() * k3);
            y = yi + data->getStep()/6 * (k1+ 2 * k2 + 2 * k3 + k4);
            xi += data->getStep();
            rkSolution.emplace_back(xi, y);
            yi  = y;
        }
        return rkSolution;
    }
};

extern "C" ifc_BasePlugin* registerPlugin() {
    return new RungeKutta();
}
