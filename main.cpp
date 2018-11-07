/*
 * Main.cpp created by Erik Wurman and Ian Squiers.
 * 11/4/19
 */


#include <iostream>
#include "ACOTester.cpp"
#include "ACO.cpp"
#include "TSP.hpp"
//#include "ACS.hpp"
#include "Elitist.hpp"



int main(int argc, const char * argv[]) {

    if (argc != 3){
        cout << "Proper arguments are <TSP_filename> <optimalTour_filename>" <<endl;
        exit(0);
    }

    const char* tspfilename = argv[1];
    const char* optimalTour_filename = argv[2];

    TSP *tsp = new TSP(tspfilename);
    //tsp->printCities();

    //Elitist aco = *new Elitist(*tsp, 30, 1000, 1, 3, 0.5, tsp->numCities);
    ACOTester acoTester = *new ACOTester(*tsp, 30, 1000, 1, 3, 0.5, tsp->numCities);
    acoTester.basicTest(optimalTour_filename);




    /*
    const char * topologytype = argv[1];
    int num_particles = atoi(argv[2]);
    int iterations = atoi(argv[3]);
    const char * func = argv[4];
    const int dimensions = atoi(argv[5]);
    */

}
