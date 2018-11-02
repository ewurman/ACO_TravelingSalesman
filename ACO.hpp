
#ifndef ACO_HPP
#define ACO_HPP

#include <vector>
#include "utils.cpp"
#include "TSP.hpp"

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


#endif