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

ACS::ACS(TSP tsp, int numAnts, int maxIterations, double alpha, double beta, double rho, double q_naught, double tau_naught, double epsilon)
: ACO(tsp, numAnts, maxIterations, alpha, beta, rho){
    if (DEBUG_ON){
        cout << "Created ACS object" <<endl;
    }
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
    vector<int>::iterator it = find(cities_remaining.begin(), cities_remaining.end(), curr_city);
    if (it != cities_remaining.end()) {
        cities_remaining.erase(it);
    }
    while (cities_remaining.size() >= 0) {
        double r = (double)rand() / RAND_MAX;
        if (r < q_naught) {
            next_city = greedy_selection(curr_city, cities_remaining);
        } else {
            next_city = prob_selection(curr_city, cities_remaining);
        }
        tour_eval+=distances[curr_city][next_city];
        tour.push_back(next_city);
        local_pupdate(curr_city, next_city);
    }
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

double ACS::sum_options(int curr_city, vector<int> cities_remaining) {
    double sum = 0;
    for (int i = 0; i < cities_remaining.size(); i++) {
        double tau = pheromones[curr_city][cities_remaining[i]];
        double distance = distances[curr_city][cities_remaining[i]];
        double eta = 1/distance;
        double tau_eta = pow(tau, alpha) * pow(eta, beta);
        sum += tau_eta;
    }
    return sum;
}

int ACS::prob_selection(int curr_city, vector<int> cities_remaining) {
    vector<pair<int, double>> probabilities;
    vector<double> bounds;
    for (int i = 0; i < cities_remaining.size(); i++) {
        double sum = sum_options(curr_city, cities_remaining);
        double tau = pheromones[curr_city][cities_remaining[i]];
        double distance = distances[curr_city][cities_remaining[i]];
        double eta = 1/distance;
        double tau_eta = pow(tau, alpha) * pow(eta, beta);
        probabilities.push_back(make_pair(tau_eta/sum, cities_remaining[i]));
    }
    // sort and set bounds
    double last = 0;
    sort(probabilities.begin(), probabilities.end());
    for (int i = (int)probabilities.size() - 1; i >= 0; i--) {
        probabilities[i].first += last;
        last+= probabilities[i].first;
    }
    // select from probabilities
    double r = (double)rand() / (double)RAND_MAX;
    for (int i = (int)probabilities.size() - 1; i >= 0; i--) {
        if (r < probabilities[i].first) {
            return probabilities[i].second;
        }
    }
    return probabilities[0].second; // shouldnt get here
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
