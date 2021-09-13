//
// Created by Seeksub on 14.11.2019.
//

#ifndef LAB1_INTERFACENUMMETHODPLUGIN_H
#define LAB1_INTERFACENUMMETHODPLUGIN_H

#include "interfaceBasedPlugin.h"

class ifc_NumericalMethodPlugin : public ifc_BasePlugin {
public:
    virtual char* getInterfaceName(char* o_name) const {
        strcpy(o_name, "ifc_NumericalMethodPlugin");
        return o_name;
    }
    virtual bool isInstanceOf(const char* p_interface_name) const {
        return strcmp(p_interface_name , "ifc_NumericalMethodPlugin")==0;
    };

    virtual vector<Points>solver(inputData*, Normalization*, Points, dFunc*) = 0;

    ifc_NumericalMethodPlugin() = default;
    ~ifc_NumericalMethodPlugin() = default;

};

#endif //LAB1_INTERFACENUMMETHODPLUGIN_H
