//
//  ACO.cpp
//  
//
//  Created by Ian Squiers on 11/1/18.
//

#include <stdio.h>
#include "ACO.hpp"
#include <float.h>
#include <iostream>


/*
select_next_city(currentCity, cities_left vector):  
    //currentCity and next city can be id# for the cities
    At the begining of each ant's tour, we deep copy the cities from TSP
    When we return this next city, we can then remove that id from the vector of cities left.


*/


ACO::ACO(TSP tsp, int numAnts, int maxIterations, double alpha, double beta, double rho){
    if (DEBUG_ON){
        cout << "Started ACO object constructor" << endl;
    }
    this->tsp = tsp;
    this->numAnts = numAnts;
    this->maxIterations = maxIterations;
    this->alpha = alpha;
    this->beta = beta;
    this->rho = rho;
    this->bestTourSoFar = vector<int>();
    this->pheromones = (double**) malloc(sizeof(double*) * this->tsp.numCities);
    this->distances = (double**) malloc(sizeof(double*) * this->tsp.numCities);
    for (int i = 0; i < this->tsp.numCities; i++){
        distances[i] = (double*) malloc(sizeof(double*) * this->tsp.numCities); 
        for (int j = 0; j < this->tsp.numCities; j++){
            City city_i = tsp.cities[i];
            City city_j = tsp.cities[j];
            distances[i][j] = city_i - city_j;
        }
    }
    // now that we have distances, we can make the nearest neighbor tour and then give intial pheromone values
    vector<int> heuristicTour = this->nearestNeighborTour();
    double heuristicTourLength = this->evaluateTour(heuristicTour);
    this->bestDistanceSoFar = heuristicTourLength;
    for (int i = 0; i < this->tsp.numCities; i++){
        pheromones[i] = (double*) malloc(sizeof(double) * this->tsp.numCities);
        bestTourSoFar.push_back(heuristicTour[i]);
        for (int j = 0; j < this->tsp.numCities; j++){
            pheromones[i][j] = (double) this->numAnts / heuristicTourLength;
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

vector<int> ACO::nearestNeighborTour(){
    vector<int> tour;
    vector<int> cities_remaining;
    for (int i = 1; i < this->tsp.numCities; i++) {
        cities_remaining.push_back(i); // create vect of city ids
    }
    int next_city = 0;
    // start with city 0
    tour.push_back(next_city);
    for (int i = 1; i < this->tsp.numCities; i++){
        //now we select the next city
        next_city = select_nearest_remaining(next_city, cities_remaining);
        tour.push_back(next_city);
        cities_remaining.erase(std::remove(cities_remaining.begin(), cities_remaining.end(), next_city), cities_remaining.end()); 
        // previous line adapted from stackoverflow how to remove single element by value in vector
    }
    tour.push_back(0); //end with first city too
    return tour;
}

int ACO::select_nearest_remaining(int city_id, vector<int> cities_remaining){
    double bestDist = DBL_MAX;
    int next_city = city_id; //placeholder
    for (int i = 0; i < cities_remaining.size(); i++){
        double distToNextCity = distances[city_id][cities_remaining[i]];
        if (distToNextCity < bestDist){
            bestDist = distToNextCity;
            next_city = cities_remaining[i];
        }
    }
    return next_city;
}

void ACO::search(double maxTime){
    cout << "WARNING: called ACO search!!!!" << endl;
}

vector<double> ACO::timedSearch(double optimalDist, vector<double> benchmarks, double maxTime){
    cout << "WARNING: called ACO timedSearch!!!!" << endl;
    return *new vector<double>();
}

void ACO::reset(){
    this->bestTourSoFar.clear();
    vector<int> heuristicTour = this->nearestNeighborTour();
    double heuristicTourLength = this->evaluateTour(heuristicTour);
    this->bestDistanceSoFar = heuristicTourLength;
    for (int i = 0; i < this->tsp.numCities; i++){
        bestTourSoFar.push_back(heuristicTour[i]);
        for (int j = 0; j < this->tsp.numCities; j++){
            pheromones[i][j] = (double) this->numAnts / heuristicTourLength;
        }
    }
}





