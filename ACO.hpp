
#ifndef ACO_HPP
#define ACO_HPP

#include <vector>
#include "utils.cpp"
#include "TSP.cpp"

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

        vector<int> nearestNeighborTour();
        int select_nearest_remaining(int city_id, vector<int> cities_remaining);

        virtual void search();

        vector<int> getBestTour() { return bestTourSoFar; }
        double getBestTourDistance() {return bestDistanceSoFar; }
        /*
        int select_next_city(currentCity, cities_left vector):  
            //currentCity and next city can be id# for the cities
            At the begining of each ant's tour, we deep copy the cities from TSP
            When we return this next city, we can then remove that id from the vector of cities left.
        */

};


#endif