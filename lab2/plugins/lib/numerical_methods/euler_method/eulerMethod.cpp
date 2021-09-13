//
// Created by Seeksub on 03.10.2019.
//
#include "../numerical_methods.h"
#include "../../../interfaceNumMethodPlugin.h"

class Euler : public ifc_NumericalMethodPlugin {
public:
    char* GetPluginName(char* o_name)const{
        strcpy(o_name, "Euler");
        return o_name;
    }
    virtual bool isInstanceOf(const char* p_interface_name) const {
        return strcmp(p_interface_name , "Euler")==0 ? true: ifc_NumericalMethodPlugin::isInstanceOf(p_interface_name);
    }
    vector<Points>solver(inputData *data, Normalization *Norma, Points p, dFunc *f) {
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
};

extern "C" ifc_BasePlugin* registerPlugin() {
    return new Euler();
}

