//
// Created by Seeksub on 18.10.2019.
//

#ifndef LAB1_INTERFACEBASEDPLUGIN_H
#define LAB1_INTERFACEBASEDPLUGIN_H

#include "lib/numerical_methods/numerical_methods.h"
#include <string>
#include <fstream>

class ifc_BasePlugin {
public:
    virtual char* getInterfaceName(char* o_name) const {
        strcpy(o_name, "interface_BasePlugin");
        return o_name;
    }
    virtual bool isInstanceOf(const char* p_interface_name) const {
        return strcmp(p_interface_name , "interface_BasePlugin")==0;
    };
    virtual char* GetPluginName(char* o_name)const = 0;

    virtual ~ifc_BasePlugin()= default;
};

typedef ifc_BasePlugin* RegisterPlugin();

#endif //LAB1_INTERFACEBASEDPLUGIN_H
