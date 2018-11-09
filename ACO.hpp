
#ifndef ACO_HPP
#define ACO_HPP

#include <vector>
#include "utils.hpp"
#include "TSP.hpp"

class ACO {

    protected:
        const static bool DEBUG_ON = true;

        TSP* tsp; // holds the cities
        int numAnts; 
        int maxIterations;
        double alpha; //influence of pheromones
        double beta;  //influence of heuristic (distance)
        double rho; //evaporationFactor
        vector<int> bestTourSoFar;
        double bestDistanceSoFar;
        
    public:
        
        double** pheromones;
        double** distances;
        ACO(TSP* tsp, int numAnts, int maxIterations, double alpha, double beta, double rho);

        double evaluateTour(vector<int> tour);

        vector<int> nearestNeighborTour();
        int select_nearest_remaining(int city_id, vector<int> cities_remaining);

        virtual void search(double maxTime);
        virtual vector<double> timedSearch(double optimalDist, vector<double> benchmarks, double maxTime);

        vector<int> getBestTour() { return bestTourSoFar; }
        double getBestTourDistance() {return bestDistanceSoFar; }

        void reset();
};


#endif
