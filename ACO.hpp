
#ifndef ACO_HPP
#define ACO_HPP

#include <vector>
#include "utils.cpp"
#include "TSP.cpp"

class ACO {

    private:
        TSP tsp; // holds the cities
        int numAnts;
        int maxIterations;
        double alpha; //influence of pheremones
        double beta;  //influence of heuristic (distance)
        double rho; //evaporationFactor

    public:
        
        double** pheremones;
        double** dinstances;
        ACO();

        /*
        int select_next_city(currentCity, cities_left vector):  
            //currentCity and next city can be id# for the cities
            At the begining of each ant's tour, we deep copy the cities from TSP
            When we return this next city, we can then remove that id from the vector of cities left.
        */

};


#endif