//
// Created by Seeksub on 14.11.2019.
//

#ifndef LAB1_INTERFACEVISUALIZERPLUGIN_H
#define LAB1_INTERFACEVISUALIZERPLUGIN_H

#include "interfaceBasedPlugin.h"

class ifc_VisualizerPlugin : public ifc_BasePlugin {
public:
    virtual char* getInterfaceName(char* o_name) const {
        strcpy(o_name, "ifc_VisualizerPlugin");
        return o_name;
    }
    virtual bool isInstanceOf(const char* p_interface_name) const {
        return strcmp(p_interface_name , "ifc_VisualizerPlugin")==0;
    };
//plotter
    virtual void plotter(string, string) = 0;
//    virtual void plotSolution(string) = 0;
//    virtual void plotNormalization(string) = 0;
//    csv
    virtual pair<string, string> csvFile(Solutions, string, vector<double>, string) = 0;
//    virtual string csvGenerator(Solutions) = 0;
//    virtual string csvGenerator() = 0;
//    virtual void csvGeneratorN(vector<double>, string) = 0;
//    virtual void csvGeneratorN() = 0;

    ifc_VisualizerPlugin() = default;
    ~ifc_VisualizerPlugin() = default;

};

#endif //LAB1_INTERFACEVISUALIZERPLUGIN_H
