#include "main.h"


using namespace std;

//set input values(checkout numerical_methods.h)
inputData data(0.1, 1, 9.8, 2, 2.);
vector<Normalization> L;
vector<double> L2;
//duo for velocity and time(checkout numerical_methods.h)
Points pdata(0.0, 0.1);
double eL1, eL2, rkL1, rkL2;

double derivativeFunc(double f) {
    return data.getGrav() - data.getAlpha() * f / data.getMass();
}

double analyticalFunc(double t) {
    return data.getMass() * data.getGrav() / data.getAlpha() * ( 1 -  exp(- data.getAlpha() * t / data.getMass()));
}

vector<std::string> get_plugins(const string &path) {
    DIR *dir;
    struct dirent *ent;
    vector<string> fileNames;
    if ((dir = opendir(path.c_str())) != nullptr) {
        while ((ent = readdir(dir)) != nullptr) {
            fileNames.emplace_back(ent->d_name);
        }
        closedir(dir);
    } else {
        perror("");
    }
    return fileNames;
}


//string csvGenerator(vector<Points> aPoints, vector<Points> ePoints, vector<Points> rkPoints){
//    //generate curr time to set the unique file name
//    time_t t = time(0);
//    struct tm *now = localtime(& t);
//    char buffer [80];
//    strftime(buffer, 80,"%Y-%m-%d_%H_%M_%S.csv", now);
//    string str(buffer);
//    ofstream file(buffer, ios::out);
//    file << "xi; "
//            << "yi_e; "
//            << "yi_rk; "
//            << "yi_a"<< endl;
//    for(int i = 0; i < aPoints.size(); i++)
//        file << aPoints[i].first << "; "
//            << ePoints[i].second << "; "
//            << rkPoints[i].second << "; "
//            << aPoints[i].second << endl;
//    file.close();
//    return str;
//}

//void csvNormGenerator(double Norma1, double Norma2, string fileName){
//    ofstream file(fileName, ios::app);
//    file << data.getStep() << "; "
//         <<Norma1 << "; "
//         <<Norma2 << endl;
//    file.close();
//}

int main(int argc, char** argv) {
    std::vector<ifc_NumericalMethodPlugin*> solverPlugins;
    std::vector<ifc_VisualizerPlugin*> visualPlugins;
    char plug_buff[512];
    vector<string> plugins = get_plugins("../lib/");
#ifdef __APPLE__
    const char* plug_name_rgx = "(.*)[.](dylib)";
#elif  defined(__linux__)
    const char* plug_name = "(.*)[.](so)";
#endif
    if (plugins.empty()) {
        cout << "There is no installed plugins" << endl;
        return -1;
    }

    void* dll;
    for(auto & plugin : plugins) {
        cout<<plugin<<endl;
        if (regex_match(plugin, regex(plug_name_rgx) )) {

            dll = dlopen(plugin.c_str(), RTLD_LAZY);
            if (dll) {
                cout << "Opened plugin with filename: " << plugin << endl;
                RegisterPlugin *reg_plugin = (RegisterPlugin*) (dlsym(dll, "registerPlugin"));
                cout<<"Regplug:" << reg_plugin << endl;
                if (reg_plugin) {
                    ifc_BasePlugin *regPlugin = reg_plugin();
                    if (regPlugin->isInstanceOf("ifc_NumericalMethodPlugin")) {
                        solverPlugins.emplace_back((ifc_NumericalMethodPlugin*)regPlugin);
                        cout << "Registered solver regPlugin: " << regPlugin->GetPluginName(plug_buff) << endl;
                    } else
                    if (regPlugin->isInstanceOf("ifc_VisualizerPlugin")) {
                        visualPlugins.emplace_back((ifc_VisualizerPlugin*)regPlugin);
                        cout << "Registered visual regPlugin: " << regPlugin->GetPluginName(plug_buff) << endl;
                    }
                } else {
                    cerr << "Unable to load function of plugin registration" << endl;
                }
            } else {
                cerr << "Unable to open plugin: " << plugin << std::endl;
            }
        }
    }

    Solutions result;
    int offset = solverPlugins.size();

    for (auto solverPlugin : solverPlugins) {
        L.emplace_back(Normalization());
        result.emplace_back(solverPlugin->solver(&data, &L[solverPlugins.size() - offset], pdata, &derivativeFunc));
        offset--;

    }

    //analytical solution
    double xi = pdata.first;
    vector<Points> aSolution;
    aSolution.emplace_back(pdata.first, pdata.second);

    //normalization
    L.emplace_back(Normalization());

    L[solverPlugins.size()].addToL1(pdata.second);
    L[solverPlugins.size()].addToL2(pdata.second);
    while(xi < data.getSimTime()){
        xi += data.getStep();
        aSolution.emplace_back(xi, analyticalFunc(xi));
        //calc normalization
        L[solverPlugins.size()].addToL1(analyticalFunc(xi));
        L[solverPlugins.size()].addToL2(analyticalFunc(xi));
    }
    L2.insert(L2.begin(), pdata.first);
    for(int j = 0 ; j < L.size(); j++) {
        double L2_calc = 0;
        for (int i = 0; i < L[j].getL2().size(); i++) {
            L2_calc += pow(L[j].getL1()[i] - L[solverPlugins.size()].getL1()[i], 2);
        }
        L2_calc = sqrt(L2_calc)/L[j].getL2().size();
        L2.emplace_back(L2_calc);
        L2_calc = 0.0;
    }

    result.emplace_back(aSolution);

    for (auto visualPlugin: visualPlugins) {
        pair<string, string> File = visualPlugin->csvFile(result, "result.csv", L2, "norma.csv");
        visualPlugin->plotter(File.first, File.second);
    }
    return 0;
}