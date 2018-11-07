/*
Elitist Ant System Code
By Erik Wurman and Ian Squiers
*/

#include "Elitist.hpp"
#include <vector>
#include <math.h>
#include <iostream>

using namespace std;

Elitist::Elitist(TSP tsp, int numAnts, int maxIterations, double alpha, double beta, double rho, double elitismFactor)
: ACO(tsp, numAnts, maxIterations, alpha, beta, rho){
    this->elitismFactor = elitismFactor;
}

void Elitist::search(){
    //This is the main loop
    vector< vector<int> > tours = *new vector< vector<int> >();
    vector<double> tourLengths = *new vector<double>();
    for (int i = 0; i < this->maxIterations; i++){
        for (int j = 0; j < this->numAnts; j++) {
            vector<int> tour = run_tour();
            
            //update if bestSoFar
            double tourDist = this->evaluateTour(tour);

            if (tourDist < this->bestDistanceSoFar){ 
                this->bestDistanceSoFar = tourDist;
                for (int k = 0; k < this->tsp.numCities; k++){ //Deep Copy
                    this->bestTourSoFar[k] = tour[k];
                }
                if (DEBUG_ON){
                    cout << "Found a new bestTour of length " << tourDist << endl;
                    printvect(tour);
                }

            }
            //add to our vector of tours and lengths
            tours.push_back(tour);
            tourLengths.push_back(tourDist);
        }
        //Now we should evaporate then update the pheromones for these tours
        evaporatePheromones();
        updatePheromones(tours, tourLengths);
        updateBestSoFarPheromones();

        tours.clear();
        tourLengths.clear();
        if (i != 0 && i % 100 == 0){
            cout << "Finished " << i << "th iteration" << endl;
        }
    }
}



/*
    This function acts the same way as search, but keeps track of when you
    find a solution benchmarks[0] , benchmarks[1], benchmarks[2], etc. of the optimal
*/
vector<double> Elitist::timedSearch(double optimalDist, vector<double> benchmarks){
    vector<double> times = *new vector<double>();
    //This is the main loop
    vector< vector<int> > tours = *new vector< vector<int> >();
    vector<double> tourLengths = *new vector<double>();

    int benchmarksIndex = 0;
    clock_t startTime = clock();
    clock_t lastImprovement = startTime;
    for (int i = 0; i < this->maxIterations; i++){
        for (int j = 0; j < this->numAnts; j++) {
            vector<int> tour = run_tour();
            
            //update if bestSoFar
            double tourDist = this->evaluateTour(tour);

            if (tourDist < this->bestDistanceSoFar){ 
                this->bestDistanceSoFar = tourDist;
                for (int k = 0; k < this->tsp.numCities; k++){ //Deep Copy
                    this->bestTourSoFar[k] = tour[k];
                }
                lastImprovement = clock();
                if (tourDist < benchmarks[benchmarksIndex]*optimalDist && benchmarksIndex <= benchmarks.size() - 1){
                    clock_t now = clock();
                    while (tourDist < benchmarks[benchmarksIndex]*optimalDist && benchmarksIndex <= benchmarks.size() - 1){
                        times.push_back( double( now - startTime ) / (double)CLOCKS_PER_SEC );
                        benchmarksIndex++;
                    }
                }

            }
            //add to our vector of tours and lengths
            tours.push_back(tour);
            tourLengths.push_back(tourDist);
        }
        //Now we should evaporate then update the pheromones for these tours
        evaporatePheromones();
        updatePheromones(tours, tourLengths);
        updateBestSoFarPheromones();

        tours.clear();
        tourLengths.clear();
        if (i != 0 && i % 100 == 0){
            cout << "Finished " << i << "th iteration" << endl;
        }
    }
    times.push_back(double( lastImprovement - startTime ) / (double)CLOCKS_PER_SEC);
    return times;
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
        double tau = this->pheromones[curr_city][cities_remaining[i]];
        double distance = this->distances[curr_city][cities_remaining[i]];
        if (distance == 0){
            return cities_remaining[i];
        }
        double eta = 1/distance;
        double tau_eta = pow(tau, this->alpha) / pow(distance, this->beta);
        /*if (DEBUG_ON){
            cout << "tau " << tau <<endl;
            cout << "distance " << distance << "   eta " << eta << endl;
            cout << "tau_eta " << tau_eta << endl;
        }*/
        sumProbs += tau_eta;
        probsUpperBounds[i] = sumProbs;
    }

    double probForNext = randomDoubleInRange(0,sumProbs);
    /*if (DEBUG_ON){
        cout << "sumProbs is " << sumProbs << endl;
        cout << "nextCity probability in selectNext() is " << probForNext << endl;
    }*/
    int i = 0;
    while (probsUpperBounds[i] < probForNext){
        i++;
    }
    return cities_remaining[i] ;

}


void Elitist::updatePheromones(vector< vector<int> > tours, vector<double> tourLengths){
    for (int i =0; i < tours.size(); i++){
        vector<int> tour = tours[i];
        double tourDist = tourLengths[i];
        for (int j = 0; j< tour.size() - 1; j++){
            // update the pheromones
            int thisCity = tour[j];
            int nextCity = tour[j+1];
            pheromones[thisCity][nextCity] += (double) 1 / tourDist;
            pheromones[nextCity][thisCity] += (double) 1 / tourDist; //we want it always to be symmetric
        }
        //Now do the final leg
        pheromones[tour[0]][tour[tour.size() - 1]] += (double) 1 / tourDist;
        pheromones[tour[tour.size() - 1]][tour[0]] += (double) 1 / tourDist;
    }
}

void Elitist::updateBestSoFarPheromones(){
    for (int i = 0; i < this->bestTourSoFar.size() - 1; i++){
        int thisCity = this->bestTourSoFar[i];
        int nextCity = this->bestTourSoFar[i+1];
        pheromones[thisCity][nextCity] += this->elitismFactor / this->bestDistanceSoFar;
        pheromones[nextCity][thisCity] += this->elitismFactor / this->bestDistanceSoFar;
    }
    pheromones[this->bestTourSoFar[0]][this->bestTourSoFar[this->bestTourSoFar.size() - 1]] += this->elitismFactor / this->bestDistanceSoFar;
    pheromones[this->bestTourSoFar[this->bestTourSoFar.size() - 1]][this->bestTourSoFar[0]] += this->elitismFactor / this->bestDistanceSoFar;

}

void Elitist::evaporatePheromones(){
    for (int i = 0; i < this->tsp.numCities; i++){
        for (int j = 0; j < this->tsp.numCities; j++){
            pheromones[i][j] = (1 - this->rho) * pheromones[i][j];
        }
    }
}






