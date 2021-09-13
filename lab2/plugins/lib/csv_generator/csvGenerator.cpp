//
// Created by Seeksub on 15.11.2019.
//

#include "../../interfaceVisualizerPlugin.h"

class csvGen: public ifc_VisualizerPlugin {

    char* GetPluginName(char* o_name)const{
        strcpy(o_name, "csvGen");
        return o_name;
    }
//Generate CSV qfile with normalization Data
    void csvGeneratorN(vector<double> Norma, string fileName) {
        ofstream file(fileName, ios::app);
//        file << data->getStep() << "; "
//             << Norma1 << "; "
//             << Norma2 << endl;
//        file << "xi; "
//            << "L1; "
//            << "L2; "
//            << "L3; "
//            << "L4" << endl;
        for(int i = 0; i < Norma.size()-1; i++) {
            if(i < Norma.size()-2)
                file << Norma[i] << "; ";
            else
                file << Norma[i] << endl;
        }

        file.close();
    }

//Generate CSV file with  Data solution
    void csvGenerator(Solutions sPoints, string csvFile) {
//        time_t t = time(0);
//        struct tm *now = localtime(&t);
//        char buffer[80];
//        strftime(buffer, 80, "%Y-%m-%d_%H_%M_%S.csv", now);
//        string str(buffer);
        ofstream file(csvFile, ios::out);
        file << "xi; "
             << "yi_e; "
             << "yi_rk; "
             << "yi_ab; "
             << "yi_h; "
             << "yi_a" << endl;
        for(int j = 0; j < sPoints[0].size(); j++)
            for (int i = 0; i < sPoints.size(); i++) {
                if(i==0) {
                    file << sPoints[i][j].first << "; ";
                file << sPoints[i][j].second << "; ";
            }
                if((i > 0) && (i != sPoints[i].size()-1))
                    file << sPoints[i][j].second << "; ";
                if(i == sPoints.size()-1)
                    file << sPoints[i][j].second << endl;
            }
        file.close();
//         return str;
    }

    void plotter(string str1, string str2){

    }

    pair<string, string> csvFile(Solutions sPoints, string csvFile, vector<double>Norma, string csvNorma){
        csvGenerator(sPoints, csvFile);
        csvGeneratorN(Norma, csvNorma);

        return make_pair(csvFile, csvNorma);
    }

};


extern "C" ifc_BasePlugin* registerPlugin() {
    return new csvGen();
}
