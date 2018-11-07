//
//  ACS.cpp
//  ACO
//
//  Created by Ian Squiers on 11/1/18.
//  Copyright © 2018 Ian Squiers. All rights reserved.
//

#include "ACS.hpp"
#include <math.h>
#include <iostream>

using namespace std;


vector<int> city_ids(int num_cities) {
    vector<int> city_ids;
    for (int i = 0; i < num_cities; i++) {
        city_ids.push_back(i);
    }
    return city_ids;
}// create vect of city ids

ACS::ACS(TSP tsp, int numAnts, int maxIterations, double alpha, double beta, double rho, double q_naught_in, double epsilon_in)
: ACO(tsp, numAnts, maxIterations, alpha, beta, rho){
    if (DEBUG_ON){
        cout << "Created ACS object" <<endl;
    }
    vector<int> heuristicTour = this->nearestNeighborTour();
    double heuristicTourLength = this->evaluateTour(heuristicTour);
    tau_naught = 1/(double)tsp.numCities * heuristicTourLength;
    q_naught = q_naught_in;
    epsilon = epsilon_in;
}

void ACS::search() {
    for (int i = 0; i < maxIterations; i++) {
        for(int j = 0; j < numAnts; j++){
            run_tour();
        }
    }
}

void ACS::run_tour() {
    vector<int> cities_remaining = city_ids(tsp.numCities); // create vect of city ids
    vector<int> tour;
    double tour_eval = 0;
    int next_city;
    int curr_city = 0;
    tour.push_back(curr_city);
    cities_remaining.erase(std::remove(cities_remaining.begin(), cities_remaining.end(), curr_city), cities_remaining.end());
    while (cities_remaining.size() > 0) {
        double r = (double)rand() / RAND_MAX;
        if (r < q_naught) {
            next_city = greedy_selection(curr_city, cities_remaining);
        } else {
            next_city = prob_selection(curr_city, cities_remaining);
        }
        tour_eval+=distances[curr_city][next_city];
        tour.push_back(next_city);
        local_pupdate(curr_city, next_city);
        cities_remaining.erase(std::remove(cities_remaining.begin(), cities_remaining.end(), next_city), cities_remaining.end());
        curr_city = next_city;
    }
    // go home
    tour_eval+=distances[curr_city][0];
    tour.push_back(0);
    
    if (tour_eval > best_eval) {
        btsf.swap(tour);
        best_eval = tour_eval;
    }
}

int ACS::greedy_selection(int curr_city, vector<int> cities_remaining) {
    double max = 0;
    int selection = -1;
    for (int i = 0; i < cities_remaining.size(); i++) {
        double tau = pheromones[curr_city][cities_remaining[i]];
        double distance = distances[curr_city][cities_remaining[i]];
        double eta = 1/distance;
        double tau_eta = tau * pow(eta, beta);
        if (tau_eta > max) {
            selection = cities_remaining[i];
        }
    }
    return selection;
}



int ACS::prob_selection(int curr_city, vector<int> cities_remaining) {
    double sumProbs = 0;
    vector<double> probsUpperBounds = *new vector<double>(cities_remaining.size());
    for (int i = 0; i < cities_remaining.size(); i++){
        double tau = this->pheromones[curr_city][cities_remaining[i]];
        double distance = this->distances[curr_city][cities_remaining[i]];
        if (distance == 0){
            return cities_remaining[i];
        }
        // double eta = 1/distance;
        double tau_eta = pow(tau, this->alpha) / pow(distance, this->beta);
        sumProbs += tau_eta;
        probsUpperBounds[i] = sumProbs;
    }
    
    double probForNext = randomDoubleInRange(0,sumProbs);
    int i = 0;
    while (probsUpperBounds[i] < probForNext){
        i++;
    }
    return cities_remaining[i] ;
}

void ACS::local_pupdate(int i, int j) {
    pheromones[i][j] = (1-epsilon) * pheromones[i][j] + epsilon * tau_naught;
}

void ACS::global_pupdate(vector<int> best_tour) {
    int lim = (int)best_tour.size() - 2;
    for (int i = 0; i < lim; i++) {
        pheromones[i][i+1] = (1 - rho)*pheromones[i][i+1] + rho*(1/best_eval);
    }
}

//to do
// pheromone update rules
//
