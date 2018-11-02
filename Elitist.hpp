
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
        double** dinstances
        ACO();

}
*/

class Elitist : ACO {
    private:
        double elitismFactor;

}

#endif