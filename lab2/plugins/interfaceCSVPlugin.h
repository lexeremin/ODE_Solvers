//
// Created by Seeksub on 15.11.2019.
//

#ifndef LAB1_INTERFACECSVPLUGIN_H
#define LAB1_INTERFACECSVPLUGIN_H

#include "interfaceBasedPlugin.h"

class ifc_CSVPlugin : public ifc_BasePlugin {
public:
//    virtual char* getInterfaceName(char* o_name) const {
//        strcpy(o_name, "ifc_CSVPlugin");
//        return o_name;
//    }
    char* GetPluginName(char* o_name)const{
        strcpy(o_name, "ifc_CSVPlugin");
        return o_name;
    }
    virtual bool isInstanceOf(const char* p_interface_name) const {
        return (strcmp(p_interface_name , "ifc_CSVPlugin")==0) ? true : false;
    };

//    virtual void csvGenerator(vector<Points>, vector<Points>, string);
//    virtual void csvGenerator(vector<Points>, vector<Points>, vector<Points>);
    virtual void csvGenerator();
    virtual string csvGenerator();
    virtual ~ifc_VisualizerPlugin();

};

#endif //LAB1_INTERFACECSVPLUGIN_H
