//
//  ACO.cpp
//  
//
//  Created by Ian Squiers on 11/1/18.
//

#include <stdio.h>
#include "ACO.hpp"
#include <float.h>


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
    this->bestTourSoFar = *new vector<int>();
    this->bestDistanceSoFar = DBL_MAX;
    this->pheromones = (double**) malloc(sizeof(double*) * this->tsp.numCities);
    this->distances = (double**) malloc(sizeof(double*) * this->tsp.numCities);
    for (int i = 0; i < this->tsp.numCities; i++){
        bestTourSoFar.push_back(i); // placeholder
        pheromones[i] = (double*) malloc(sizeof(double*) * this->tsp.numCities);
        distances[i] = (double*) malloc(sizeof(double*) * this->tsp.numCities); 
        for (int j = 0; j < this->tsp.numCities; j++){
            City city_i = tsp.cities[i];
            City city_j = tsp.cities[j];
            distances[i][j] = city_i - city_j;
        }
    }

}


double ACO::evaluateTour(vector<int> tour){
    double distance = 0;
    for(int i = 0; i < this->tsp.numCities - 1; i++){
        int thisCity = tour[i];
        int nextCity = tour[i+1];
        distance += this->distances[thisCity][nextCity];
    }
    // May not have to do final leg
    distance += this->distances[tour[0]][tour[tour.size() - 1]];
    return distance;

}






