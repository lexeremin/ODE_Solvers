#include <iostream>
#include <dlfcn.h>
#include <fstream>
#include <ctime>
#include "../lib/numerical_methods/numerical_methods.h"

using namespace std;

//set input values(checkout numerical_methods.h)
inputData data(1.1, 1, 9.8, 2, 2.);
Normalization eL, rkL, aL;
//duo for velocity and time(checkout numerical_methods.h)
Points pdata(0.0, 0.1);
double eL1, eL2, rkL1, rkL2;
double derivativeFunc(double f) {
    return data.getGrav() - data.getAlpha() * f / data.getMass();
}

double analyticalFunc(double t) {
    return data.getMass() * data.getGrav() / data.getAlpha() * ( 1 -  exp(- data.getAlpha() * t / data.getMass()));
}

string csvGenerator(vector<Points> aPoints, vector<Points> ePoints, vector<Points> rkPoints){
    //generate curr time to set the unique file name
    time_t t = time(0);
    struct tm *now = localtime(& t);
    char buffer [80];
    strftime(buffer, 80,"%Y-%m-%d_%H_%M_%S.csv", now);
    string str(buffer);
    ofstream file(buffer, ios::out);
    file << "xi; "
            << "yi_e; "
            << "yi_rk; "
            << "yi_a"<< endl;
    for(int i = 0; i < aPoints.size(); i++)
        file << aPoints[i].first << "; "
            << ePoints[i].second << "; "
            << rkPoints[i].second << "; "
            << aPoints[i].second << endl;
    file.close();
    return str;
}

void csvNormGenerator(double Norma1, double Norma2, string fileName){
    ofstream file(fileName, ios::app);
    file << data.getStep() << "; "
         <<Norma1 << "; "
         <<Norma2 << endl;
    file.close();
}

int main(int argc, char** argv) {
    //load libraries
#ifdef __APPLE__
    void *lib_handler1 = dlopen("libeuler_method.dylib", RTLD_LAZY);
    void *lib_handler2 = dlopen("librunge-kutta_method.dylib", RTLD_LAZY);
    void *lib_handler3 = dlopen("libplot.dylib", RTLD_LAZY);
#elif  defined(__linux__)
    void *lib_handler1 = dlopen("libeulerMethod.so", RTLD_LAZY);
    void *lib_handler2 = dlopen("librungekuttaMethod.so", RTLD_LAZY);
    void *lib_handler3 = dlopen("libplot.dyso", RTLD_LAZY);
#endif
    //check if dynlibs were opened
    if(!lib_handler1 || !lib_handler2 || !lib_handler3) {
        fprintf(stderr, "dlopen() error: %s\n", dlerror());
        exit(EXIT_FAILURE);
    }
    //load functions from libs(checkout numerical_methods.h for Method typedef declaration)
    Method *eulerFunc, *rungekuttaFunc;
    eulerFunc = (Method *) dlsym(lib_handler1, "euler");
    rungekuttaFunc = (Method *) dlsym(lib_handler2, "rungekutta");
    //executing funcs form libs and getting solutions(checkout numerical_methods.h for vector<Points> typedef)
    vector<Points> eSolution = eulerFunc(&data, &eL, pdata, &derivativeFunc);
    vector<Points> rkSolution = rungekuttaFunc(&data, &rkL, pdata, &derivativeFunc);

    //analytical solution
    double xi = pdata.first;
    vector<Points> aSolution;
    aSolution.emplace_back(pdata.first, pdata.second);
    //normalization
    aL.addToL1(pdata.second);
    aL.addToL2(pdata.second);
    while(xi < data.getSimTime()){
        xi += data.getStep();
        aSolution.emplace_back(xi, analyticalFunc(xi));
        //calc normalization
        aL.addToL1(analyticalFunc(xi));
        aL.addToL2(analyticalFunc(xi));
    }
//    cout << "Analytical normalization L1 =" << data.getL1() << " L2 =" << data.getL2() << endl;
    //generating and writing to the file
    string file_name = csvGenerator(aSolution, eSolution, rkSolution);
    cout <<"Saved to the file named: "<< file_name << endl;
    cout << "Build done!" << endl;

    //load lib and drawing graphs of solutions
    void (*ploter)(string) = (void(*)(string))dlsym(lib_handler3, "plot");
    ploter(file_name);

    //Normalization
    void (*plotNorma)(string) = (void(*)(string))dlsym(lib_handler3, "plotNorma");
    //Normalization calculaiting
    for(int i = 0; i < eL.getL1().size(); i++){
        eL1 += fabs(eL.getL1()[i] - aL.getL1()[i]);
        eL2 += pow(eL.getL1()[i] - aL.getL1()[i], 2);
    }
    eL2 = sqrt(eL2)/eL.getL2().size();
    for(int i = 0; i < eL.getL1().size(); i++){
        rkL1 += fabs(rkL.getL1()[i] - aL.getL1()[i]);
        rkL2 += pow(rkL.getL1()[i] - aL.getL1()[i], 2);
    }
    rkL2 = sqrt(rkL2)/rkL.getL2().size();
    //writing normas and steps to the files
    csvNormGenerator(eL2, rkL2, "norma.csv");
    //drawing graphs with L1,L2(numerical methods solution) - L1,L2(analytical solution)
    plotNorma("norma.csv");

    //close libs
    dlclose(lib_handler1);
    dlclose(lib_handler2);
    dlclose(lib_handler3);
    return 0;
}