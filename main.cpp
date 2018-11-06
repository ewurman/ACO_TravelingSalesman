/*
 * Main.cpp created by Erik Wurman and Ian Squiers.
 * 11/4/19
 */


#include <iostream>
#include "ACOTester.hpp"
#include "ACO.cpp"
#include "TSP.hpp"
//#include "ACS.hpp"
#include "Elitist.cpp"



int main(int argc, const char * argv[]) {

    if (argc == 1){
        cout << "Proper arguments are <TSP_filename>" <<endl;
        exit(0);
    }

    const char* tspfilename = argv[1];

    TSP *tsp = new TSP(tspfilename);
    tsp->printCities();
    /*
    const char * topologytype = argv[1];
    int num_particles = atoi(argv[2]);
    int iterations = atoi(argv[3]);
    const char * func = argv[4];
    const int dimensions = atoi(argv[5]);
    */

}