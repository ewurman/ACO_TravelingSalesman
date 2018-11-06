
#ifndef ELITIST_HPP
#define ELITIST_HPP

#include <vector>
#include "ACO.hpp"

/*
public class ACO {

    private:
        TSP tsp; // holds the cities
        int numAnts;
        int maxIterations;
        double alpha; //influence of pheremones
        double beta;  //influence of heuristic (distance)
        double rho; //evaporationFactor

    public:
        
        double** pheremones
        double** distances
        ACO();

}
*/

class Elitist : ACO {
    private:
        double elitismFactor;
    public:

        Elitist(TSP tsp, int numAnts, int maxIterations, double alpha, double beta, double rho, double elitismFactor);
        void search();
        vector<int> run_tour();
        int select_next(int curr_city, vector<int> cities_remaining);


        
};

#endif

