


#ifndef ACSTESTER_HPP
#define ACSTESTER_HPP

#include "ACO.hpp"
#include "Elitist.hpp"
#include "ACS.hpp"

class ACOTester {
private:
    ACO* acoAlgorithm;
    
public:
    ACOTester(TSP tsp, int numAnts, int maxIterations, double alpha, double beta, double rho, double elitismFactor);
    vector<int> parseFileForOptimalTour(string filename);
    
    void basicTest(string optimal_filename);
    
    
};




#endif
