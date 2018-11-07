
#ifndef ELITIST_HPP
#define ELITIST_HPP

#include <vector>
#include "ACO.hpp"

/*
class ACO {

    protected:
        const static bool DEBUG_ON = true;

        TSP tsp; // holds the cities
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
        ACO(TSP tsp, int numAnts, int maxIterations, double alpha, double beta, double rho);

        double evaluateTour(vector<int> tour);

        vector<int> nearestNeighborTour();
        int select_nearest_remaining(int city_id, vector<int> cities_remaining);

        virtual void search();
        virtual vector<double> timedSearch();

        vector<int> getBestTour() { return bestTourSoFar; }
        double getBestTourDistance() {return bestDistanceSoFar; }

};
*/

class Elitist : public ACO {
    private:
        double elitismFactor;

    public:

        Elitist(TSP tsp, int numAnts, int maxIterations, double alpha, double beta, double rho, double elitismFactor);
        void search();
        vector<int> run_tour();
        int select_next(int curr_city, vector<int> cities_remaining);
        void updatePheromones(vector< vector<int> > tours, vector<double> tourLengths);
        void updateBestSoFarPheromones();
        void evaporatePheromones();
        vector<double> timedSearch(double optimalDist, vector<double> benchmarks);


        
};

#endif

