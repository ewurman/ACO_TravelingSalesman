//
//  ACS.cpp
//  ACO
//
//  Created by Ian Squiers on 11/1/18.
//  Copyright © 2018 Ian Squiers. All rights reserved.
//

#include "ACS.hpp"
#include <math.h>

using namespace std;

vector<int> city_ids(int num_cities) {
    vector<int> city_ids;
    for (int i = 0; i < num_cities; i++) {
        city_ids.push_back(i);
    }
    return city_ids;
}// create vect of city ids


void ACS::run_tour(char** dist, char** pheromones) {
    vector<int> cities_remaining = city_ids(this->num_cities); // create vect of city ids
    int next_city = -1;
    int curr_city = rand() % this->num_cities;
    while (cities_remaining.size() >= 0) {
        double r = (double)rand() / RAND_MAX;
        if (r < this->q_naught) {
            next_city = greedy_selection(curr_city, cities_remaining, dist, pheromones);
        } else {
            next_city = prob_selection(curr_city, cities_remaining, dist, pheromones);
        }
    }
}

int ACS::greedy_selection(int curr_city, vector<int> cities_remaining, char** dist, char** pheromones) {
    double max = 0;
    int selection = -1;
    for (int i = 0; i < cities_remaining.size(); i++) {
        double tau = pheromones[curr_city][cities_remaining[i]];
        double distance = dist[curr_city][cities_remaining[i]];
        double eta = 1/distance;
        double tau_eta = pow(tau, this->alpha) * pow(eta, this->beta);
        if (tau_eta > max) {
            selection = cities_remaining[i];
        }
    }
    return selection;
}

double ACS::sum_options(int curr_city, vector<int> cities_remaining, char** dist, char** pheromones) {
    double sum = 0;
    for (int i = 0; i < cities_remaining.size(); i++) {
        double tau = pheromones[curr_city][cities_remaining[i]];
        double distance = dist[curr_city][cities_remaining[i]];
        double eta = 1/distance;
        double tau_eta = pow(tau, this->alpha) * pow(eta, this->beta);
        sum += tau_eta;
    }
    return sum;
}

int ACS::prob_selection(int curr_city, vector<int> cities_remaining, char** dist, char** pheromones) {
    vector<pair<int, double>> probabilities;
    vector<double> bounds;
    double sum = sum_options(curr_city, cities_remaining, dist, pheromones);
    for (int i = 0; i < cities_remaining.size(); i++) {
        double tau = pheromones[curr_city][cities_remaining[i]];
        double distance = dist[curr_city][cities_remaining[i]];
        double eta = 1/distance;
        double tau_eta = pow(tau, this->alpha) * pow(eta, this->beta);
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


