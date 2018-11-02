
#ifndef ACO_HPP
#define ACO_HPP

#include <vector>
#include "utils.cpp"
#include "TSP.hpp"

class ACO {

    private:
        TSP tsp;

    public:
        
        double** pheremones
        double** dinstances
        ACO();
}

#endif