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
        double alpha; //influence of pheromones
        double beta;  //influence of heuristic (distance)
        double rho; //evaporationFactor

    public:
        
        double** pheromones
        double** dinstances
        ACO();

}
*/
using namespace std;

class ACS : public ACO {
    private:

        vector<int> btsf;
        double best_eval;
        double epsilon; //wear away factor
        double tau_naught; // Minimum pheremone concentration
        double q_naught; // probability of choosing greedily next leg
    
        void search();
        void run_tour();
        int select_next(int curr_id);
        int greedy_selection(int curr_city, vector<int> cities_remaining);
        int prob_selection(int curr_city, vector<int> cities_remaining);
        double sum_options(int curr_city, vector<int> cities_remaining);
        void local_pupdate(int i, int j);
        void global_pupdate(vector<int> best_tour);
    
    public:
        ACS(TSP tsp, int numAnts, int maxIterations, double alpha, double beta, double rho, double q_naught, double tau_naught, double epsilon);

};


#include <stdio.h>

#endif /* ACS_hpp */
