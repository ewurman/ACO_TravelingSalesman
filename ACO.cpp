//
//  ACO.cpp
//  
//
//  Created by Ian Squiers on 11/1/18.
//

#include <stdio.h>
#include "ACO.hpp"



/*
select_next_city(currentCity, cities_left vector):  
    //currentCity and next city can be id# for the cities
    At the begining of each ant's tour, we deep copy the cities from TSP
    When we return this next city, we can then remove that id from the vector of cities left.


*/

ACO::ACO(TSP tsp, int numAnts, int maxIterations, double alpha, double beta, double rho){
    this->tsp = tsp;
    this->numAnts = numAnts;
    this->maxIterations = maxIterations;
    this->alpha = alpha;
    this->beta = beta;
    this->rho = rho;
}


