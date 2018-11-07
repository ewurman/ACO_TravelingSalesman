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
#include <fstream>

int main(int argc, const char * argv[]) {

    srand(time(0));
    if (argc == 1) {

        bool recordingToFile = true;

        std::map<string, double> tspProblemsMap;
        //tspProblemsMap["u574.tsp"] = 36905;
        //tspProblemsMap["u1060.tsp"] = 224094;
        //tspProblemsMap["vm1748.tsp"] = 336556;
        tspProblemsMap["u2152.tsp"] = 64253;
        tspProblemsMap["pcb3038.tsp"] = 137694;
        tspProblemsMap["fnl4461.tsp"] = 182566;
        tspProblemsMap["rl5915.tsp"] = 565530;
        
        int ants = 15;
        double alphas[] = {1};
        double betas[] = {2,3.5,5};
        double rhos[] = {0.1, 0.5};
        double q_naughts[] = {0.7, 0.9};
        double epsilons[] = {0.1};
        int iterations = 1000;

        /* First we want to find the parameters that lead to good solutions on a small probelem for each algorithm
         * Then we want to use these parameters to compare the two algorithms on larger files
         */

        //This code here is for finding good parameters
        if (recordingToFile) {
                string header = "Factor Of Optimal, Elitist Time, ACS Time";
                string functionFilename = "u574Comparison.csv";
                fstream functionFile;
                functionFile.open(functionFilename, ios::out);
                functionFile << header << endl;
                TSP *tsp = new TSP("TestFiles/u574.tsp");
                double optimalLength = 36905;
                ACOTester acoTester = *new ACOTester(*tsp, ants, iterations, alphas[0], betas[1], rhos[1], tsp->numCities, q_naughts[0], epsilons[0]);
                vector< pair<double,double> > timesForBoth = acoTester.compareTestManyTimesTimed(optimalLength);
        }




        map<string, double>::iterator it;
        for (it = tspProblemsMap.begin(); it != tspProblemsMap.end(); it++){
            string filename = it->first;
            double optimalLength = it->second;
            TSP *tsp = new TSP(string("/Users/iansquiers/Desktop/NI/ACO_TravelingSalesman/TestFiles/") + filename);
            ACOTester acoTester = *new ACOTester(*tsp, ants, iterations, alphas[0], betas[1], rhos[1], tsp->numCities, q_naughts[0], epsilons[0]);

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
        acoTester.basicTestTimed(optimalTour_filename);
        //acoTester.basicTest(optimalTour_filename);
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


