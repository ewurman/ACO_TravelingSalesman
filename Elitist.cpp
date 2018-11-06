

#include "Elitist.hpp"
#include <vector>




Elitist::Elitist(TSP tsp, int numAnts, int maxIterations, double alpha, double beta, double rho, double elitismFactor)
: ACO(TSP tsp, int numAnts, int maxIterations, double alpha, double beta, double rho){
    this->elitismFactor = elitismFactor;
}





// ******************************************************************************************
// ****** Boltzmann Selection
// ******************************************************************************************


inline double boltz_sum(vector<Individual> pop) {
    double sum = 0;
    for (unsigned i = 0; i < pop.size(); i++) {
        sum += exp(pop[i].fitness);
    }
    return sum;
}

inline double * probablities_by_boltz(vector<Individual> pop) {
    double sum = boltz_sum(pop);
    double last_pos = 0;
    double curr_bound = 0;
    double * probability_of = new double [population_size + 1]; // no such thing as rank 0
    for (int i = (population_size); i >= 0; i--) {
        curr_bound = last_pos + (exp(pop[i].fitness) / sum);
        probability_of[i] = curr_bound;
        last_pos = curr_bound;
    }
    return probability_of;
}


// fills next pop with selected individuals ready for breeding
inline vector<Individual> boltzmann_selection( vector<> pop ) {
    vector<Individual> selected_pop;
    
    // sort the population least to most fit
    std::sort (pop.begin(), pop.end());
    
    double * probability_of = probablities_by_boltz(pop); // least to most probable by bound
    for (int i = 0; i < population_size; i++) {
        double r = (double)rand() / (double)RAND_MAX;
        for (int j = population_size; j > 0; j--) {
            if (r < probability_of[j]) {
                selected_pop.push_back(copyForBreeding(pop[j - 1], num_variables));
                break;
            }
            if (j == 1) {
                // but because of rounding the bounds are not always perfect... we'll give the most fit a boost
                selected_pop.push_back(copyForBreeding(pop[population_size - 1], num_variables));
            }
        }
    }
    delete[] probability_of;
    free_mem(pop);
    return selected_pop;
}
