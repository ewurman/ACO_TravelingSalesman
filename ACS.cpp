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
            vector<int> tour = run_tour();
            double tour_eval = this->evaluateTour(tour);
            if (tour_eval > this->bestDistanceSoFar) {
                bestTourSoFar.swap(tour);
                this->bestDistanceSoFar = tour_eval;
            }
        }
        global_pupdate(this->bestTourSoFar);

        if (i != 0 && i % 100 == 0){
            cout << "Finished ACS " << i << "th iteration" << endl;
        }
    }
}

vector<double> ACS::timedSearch(double optimalDist, vector<double> benchmarks){
    vector<double> times  = *new vector<double>();
    clock_t startTime = clock();
    clock_t lastImprovement = startTime;
    int benchmarksIndex = 0;
    for (int i = 0; i < maxIterations; i++) {
        for(int j = 0; j < numAnts; j++){
            vector<int> tour = run_tour();
            double tour_eval = this->evaluateTour(tour);
            if (tour_eval > this->bestDistanceSoFar) {
                bestTourSoFar.swap(tour);
                this->bestDistanceSoFar = tour_eval;

                //now check times to record
                lastImprovement = clock();
                if (tour_eval < benchmarks[benchmarksIndex]*optimalDist && benchmarksIndex <= benchmarks.size() - 1){
                    cout << "tour_eval " << tour_eval << endl;
                    while (tour_eval < benchmarks[benchmarksIndex]*optimalDist && benchmarksIndex <= benchmarks.size() - 1){
                        times.push_back( double( lastImprovement - startTime ) / (double)CLOCKS_PER_SEC );
                        benchmarksIndex++;
                    }
                }
            }
        }
        global_pupdate(this->bestTourSoFar);

        if (i != 0 && i % 100 == 0){
            cout << "Finished ACS " << i << "th iteration" << endl;
        }
    }
    times.push_back(double( lastImprovement - startTime ) / (double)CLOCKS_PER_SEC);
    return times;
}



vector<int> ACS::run_tour() {
    vector<int> cities_remaining = city_ids(tsp.numCities); // create vect of city ids
    vector<int> tour;
    //double tour_eval = 0;
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
        //tour_eval+=distances[curr_city][next_city];
        tour.push_back(next_city);
        local_pupdate(curr_city, next_city);
        cities_remaining.erase(std::remove(cities_remaining.begin(), cities_remaining.end(), next_city), cities_remaining.end());
        curr_city = next_city;
    }
    // go home
    //tour_eval+=distances[curr_city][0];
    tour.push_back(0);
    /*
    if (tour_eval > best_eval) {
        btsf.swap(tour);
        best_eval = tour_eval;
    }
    */
    return tour;
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
    pheromones[j][i] = (1-epsilon) * pheromones[j][i] + epsilon * tau_naught;
}

void ACS::global_pupdate(vector<int> best_tour) {
    int lim = (int)best_tour.size()-1;
    int i = 0;
    for (i=0; i < lim; i++) {
        int curr = best_tour.at(i);
        int next = best_tour.at(i+1);
        pheromones[curr][next] = (1 - rho)*pheromones[curr][next] + rho/this->bestDistanceSoFar;
        pheromones[next][curr] = (1 - rho)*pheromones[next][curr] + rho/this->bestDistanceSoFar;
    }
}

//to do
// pheromone update rules
//
