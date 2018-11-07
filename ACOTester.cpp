
#include "ACOTester.hpp"
#include <vector>
#include <fstream>
#include <math.h>
#include <iostream>
#include <string>

//bool DEBUG_ACOTESTER_ON = true;
string TOUR_SECTION = "TOUR_SECTION";
string END_OF_FILE = "EOF";
bool DEBUG_ON =false;

ACOTester::ACOTester(TSP tsp, int numAnts, int maxIterations, double alpha, double beta, double rho, 
    double elitismFactor, double q_naught, double epsilon){
    // Contructor for tests on Elitist
    this->elitistAlgorithm = new Elitist(tsp, numAnts, maxIterations, alpha, beta, rho, elitismFactor);
    this->acsAlgorithm = (ACO*) new ACS(tsp, numAnts, maxIterations, alpha, beta, rho, q_naught, epsilon);
}



vector<int> ACOTester::parseFileForOptimalTour(string filename){
    ifstream infile(filename);
    string line;
    bool foundTourSection = false;
    vector<int> tour;
    while (getline(infile, line)) { 

        if (!line.substr(0,3).compare(END_OF_FILE)) {
            return tour;
        }

        if (foundTourSection) {
            //this begins as a number
            size_t endOfNumber = line.find_first_not_of("-1234567890");
            int cityNum = stoi(line.substr(0,endOfNumber));
            cityNum = abs(cityNum);
            tour.push_back(cityNum - 1); //0 index not 1 index
        }

        int tourSectionStartIndex = (int)line.find(TOUR_SECTION);
        if (tourSectionStartIndex != std::string::npos){ //we found it
            foundTourSection = true;
        }
    }

    return tour;
}


void ACOTester::basicTest(string optimal_filename){
    vector<int> optimalTour = this->parseFileForOptimalTour(optimal_filename);
    double optimalDist = 10.0;//this->acsAlgorithm->evaluateTour(optimalTour);
    this->acsAlgorithm->search();
    vector<int> acoTour = this->acsAlgorithm->getBestTour();
    double acoDist = this->acsAlgorithm->getBestTourDistance();
    cout << "ACO Algorithm found a tour of distance " << acoDist << " while the optimal distance was " << optimalDist <<endl;
    cout << "The ACO algorithm got a tour " << acoDist / optimalDist << " times the optimal" << endl;
    cout << "The optimal Tour is: ";
    printvect(optimalTour);
}


