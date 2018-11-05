//
//  ACS.hpp
//  ACO
//
//  Created by Ian Squiers on 11/1/18.
//  Copyright © 2018 Ian Squiers. All rights reserved.
//

#ifndef ACS_hpp
#define ACS_hpp

#include "ACO.hpp"
#include <vector>

/*
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
*/
using namespace std;

class ACS {
    private:
        int num_cities; // not sure best way to access this
        double epsilon; //wear away factor
        double tau_naught; // Minimum pheremone concentration
        double q_naught; // probability of choosing greedily next leg
        void run_tour(char** dist, char** pheromones);
        int select_next(int curr_id);
        int greedy_selection(int curr_city);
        int prob_selection(int curr_city);
    
    
    public:
        double max_TauEta(int city_id);

};


#include <stdio.h>

#endif /* ACS_hpp */
