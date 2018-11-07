
#ifndef ELITIST_HPP
#define ELITIST_HPP

#include <vector>
#include "ACO.hpp"

/*
class ACO {

    protected:
        TSP tsp; // holds the cities
        int numAnts; //30-50 seems like a good idea
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

}
*/

class Elitist : public ACO {
    private:
        double elitismFactor;
        bool DEBUG_ON = true;

    public:

        Elitist(TSP tsp, int numAnts, int maxIterations, double alpha, double beta, double rho, double elitismFactor);
        void search();
        vector<int> run_tour();
        int select_next(int curr_city, vector<int> cities_remaining);
        void updatePheromones(vector< vector<int> > tours, vector<double> tourLengths);
        void updateBestSoFarPheromones();
        void evaporatePheromones();


        
};

#endif

