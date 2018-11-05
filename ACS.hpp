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


class ACS : ACO {
    private:
        double epsilon; //wear away factor
        double tau_naught; // Minimum pheremone concentration
        double q_naught; // probability of choosing greedily next leg

};


#include <stdio.h>

#endif /* ACS_hpp */
