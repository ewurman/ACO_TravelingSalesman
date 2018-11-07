/*
 * Main.cpp created by Erik Wurman and Ian Squiers.
 * 11/4/19
 */


#include <iostream>
#include "ACOTester.hpp"
#include "ACO.hpp"
#include "TSP.hpp"
#include "ACS.hpp"
#include "Elitist.hpp"
#include "utils.hpp"
#include <map>

int main(int argc, const char * argv[]) {

    srand(time(0));
    if (argc == 1) {

        std::map<string, double> tspProblemsMap;
        tspProblemsMap["u574.tsp"] = 36905;
        tspProblemsMap["u1060.tsp"] = 224094;
        tspProblemsMap["vm1748.tsp"] = 336556;
        tspProblemsMap["u2152.tsp"] = 64253;
        
        map<string, double>::iterator it;
        for (it = tspProblemsMap.begin(); it != tspProblemsMap.end(); it++){
            string filename = it->first;
            double optimalLength = it->second;
            filename = 
            TSP *tsp = new TSP(filename);
            ACOTester acoTester = *new ACOTester(*tsp, 30, 1000, 1, 3, 0.5, tsp->numCities, 0.7, 0.1);

            //Now run tests somehow
            cout << "Testing on " << filename << " which has optimal distance of " << optimalLength << endl;
            acoTester.compareTestManyTimes(optimalLength);
        }
    }
    
    else if (argc != 3){
        cout << "Proper arguments are <TSP_filename> <optimalTour_filename> to run one comparisonTest" <<endl;
        cout << "To run all tests, have no arguments" << endl;
        exit(0);
    }
    
    else if (argc == 3) {
        const char* tspfilename = argv[1];
        const char* optimalTour_filename = argv[2];
        TSP *tsp = new TSP(tspfilename);
    
        ACOTester acoTester = *new ACOTester(*tsp, 30, 1000, 1, 3, 0.5, tsp->numCities, 0.7, 0.1);
        acoTester.basicTest(optimalTour_filename);
    }

    // (TSP tsp, int numAnts, int maxIterations, double alpha, double beta, double rho, double q_naught, double tau_naught, double epsilon)

    /*
    const char * topologytype = argv[1];
    int num_particles = atoi(argv[2]);
    int iterations = atoi(argv[3]);
    const char * func = argv[4];
    const int dimensions = atoi(argv[5]);
    */

}
