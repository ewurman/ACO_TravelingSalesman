/*
Elitist Ant System Code
By Erik Wurman and Ian Squiers
*/

#include "Elitist.hpp"
#include <vector>
#include <math.h>

using namespace std;


Elitist::Elitist(TSP tsp, int numAnts, int maxIterations, double alpha, double beta, double rho, double elitismFactor)
: ACO(tsp, numAnts, maxIterations, alpha, beta, rho){
    this->elitismFactor = elitismFactor;
}


void Elitist::search(){
    //This is the main loop

    for (int i = 0; i < this->maxIterations; i++){
        for (int j = 0; j < this->numAnts; j++){
            vector<int> tour = run_tour();

            //update if bestSoFar
            double tourDist = this->evaluateTour(tour);
            if (tourDist < this->bestDistanceSoFar){ 
                this->bestDistanceSoFar = tourDist;
                for (int k = 0; k < this->tsp.numCities; k++){ //Deep Copy
                    this->bestTourSoFar[k] = tour[k];
                }
            }
        }
        //Now we should update the pheremones
    }
}


vector<int> Elitist::run_tour(){
    vector<int> tour = *new vector<int>();
    vector<int> cities_remaining;
    for (int i = 1; i < this->tsp.numCities; i++) {
        cities_remaining.push_back(i); // create vect of city ids
    }
    int next_city = 0;
    // start with city 0
    tour.push_back(next_city);
    for (int i = 1; i < this->tsp.numCities; i++){
        //now we select the next city
        next_city = select_next(next_city, cities_remaining);
        tour.push_back(next_city);
        cities_remaining.erase(std::remove(cities_remaining.begin(), cities_remaining.end(), next_city), cities_remaining.end()); 
        // previous line adapted from stackoverflow how to remove single element by value in vector
    }
    tour.push_back(0); //TODO: do we end with the starting city?
    return tour;
}


int Elitist::select_next(int curr_city, vector<int> cities_remaining) {
    double sumProbs = 0;
    vector<double> probsUpperBounds = *new vector<double>(cities_remaining.size());
    for (int i = 0; i < cities_remaining.size(); i++){
        double tau = this->pheremones[curr_city][i];
        double distance = this->distances[curr_city][i];
        double eta = 1/distance;
        double tau_eta = pow(tau, this->alpha) * pow(eta, this->beta);
        sumProbs += tau_eta;
        probsUpperBounds[i] = sumProbs;
    }
    double probForNext = randomDoubleInRange(0,sumProbs);
    int i = 0;
    while (probsUpperBounds[i] < probForNext){
        i++;
    }
    return cities_remaining[i];

}
