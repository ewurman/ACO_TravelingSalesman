//
//  ACS.cpp
//  ACO
//
//  Created by Ian Squiers on 11/1/18.
//  Copyright © 2018 Ian Squiers. All rights reserved.
//

#include "ACS.hpp"

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
            next_city = greedy_selection(curr_city);
        } else {
            next_city = prob_selection(curr_city);
        }
    }
}

int ACS::greedy_selection(int curr_city) {
}
