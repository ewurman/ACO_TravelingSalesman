


#ifndef ACOTESTER_HPP
#define ACOTESTER_HPP

#include "ACO.hpp"
#include "Elitist.hpp"
#include "ACS.hpp"

class ACOTester {
    private:
        Elitist* elitistAlgorithm;
        ACS* acsAlgorithm;
        const static int numTests = 5;
        
    public:

        ACOTester(TSP tsp, int numAnts, int maxIterations, double alpha, double beta, double rho, double elitismFactor, 
            double q_naught, double epsilon);

        vector<int> parseFileForOptimalTour(string filename);

        void basicTest(string optimal_filename);
        void compareTestOnce(double optimalDist, double& elitistResult, double& acsResult);

        void compareTestManyTimes(double optimalDist);



};




#endif
