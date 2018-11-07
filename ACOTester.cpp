
#include "ACOTester.hpp"
#include <vector>
#include <fstream>
#include <math.h>
#include <iostream>
#include <string>

//bool DEBUG_ACOTESTER_ON = true;
string TOUR_SECTION = "TOUR_SECTION";
string END_OF_FILE = "EOF";
bool DEBUG_ON = false;

ACOTester::ACOTester(TSP tsp, int numAnts, int maxIterations, double alpha, double beta, double rho, 
    double elitismFactor, double q_naught, double epsilon){
    // Contructor for tests on Elitist
    this->elitistAlgorithm = new Elitist(tsp, numAnts, maxIterations, alpha, beta, rho, elitismFactor);
    this->acsAlgorithm = new ACS(tsp, numAnts, maxIterations, alpha, beta, rho, q_naught, epsilon);
    this->timingBenchmarks = *new vector<double>();
    this->timingBenchmarks.push_back(1.30);
    this->timingBenchmarks.push_back(1.25);
    this->timingBenchmarks.push_back(1.20);
    this->timingBenchmarks.push_back(1.15);
    this->timingBenchmarks.push_back(1.10);
    this->timingBenchmarks.push_back(1.05);
    this->timingBenchmarks.push_back(1.00);
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
    double optimalDist = this->acsAlgorithm->evaluateTour(optimalTour);

    this->acsAlgorithm->search(this->maxTimeSearching);
    vector<int> acsTour = this->acsAlgorithm->getBestTour();
    double acsDist = this->acsAlgorithm->getBestTourDistance();
    cout << "ACS Algorithm found a tour of distance " << acsDist << " while the optimal distance was " << optimalDist <<endl;
    cout << "The ACS algorithm got a tour " << acsDist / optimalDist << " times the optimal" << endl;

    this->elitistAlgorithm->search(this->maxTimeSearching);
    vector<int> elitistTour = this->elitistAlgorithm->getBestTour();
    double elitistDist = this->elitistAlgorithm->getBestTourDistance();
    cout << "Elitist Algorithm found a tour of distance " << elitistDist << " while the optimal distance was " << optimalDist <<endl;
    cout << "The Elitist algorithm got a tour " << elitistDist / optimalDist << " times the optimal" << endl;

    cout << endl;
    cout << "The optimal Tour is: ";
    printvect(optimalTour);
}

void ACOTester::basicTestTimed(string optimal_filename){
    if (DEBUG_ON){
        cout << "started basicTestTimed" << endl;
    }
    vector<int> optimalTour = this->parseFileForOptimalTour(optimal_filename);
    double optimalDist = this->acsAlgorithm->evaluateTour(optimalTour);
    
    vector<double> acsTimes = this->acsAlgorithm->timedSearch(optimalDist, this->timingBenchmarks, this->maxTimeSearching);
    vector<int> acsTour = this->acsAlgorithm->getBestTour();
    double acsDist = this->acsAlgorithm->getBestTourDistance();
    for (int i = 0; i < acsTimes.size() - 1; i++){
        cout << "ACS found a tour of " << this->timingBenchmarks[i] << " the optimal in " << acsTimes[i] << " seconds" << endl;
    }
    cout << "ACS found its best tour in " << acsTimes[acsTimes.size() - 1] << " seconds" <<endl;
    cout << "ACS Algorithm found a tour of distance " << acsDist << " while the optimal distance was " << optimalDist <<endl;
    cout << "The ACS algorithm got a tour " << acsDist / optimalDist << " times the optimal" << endl;
    
    vector<double> elitistTimes = this->elitistAlgorithm->timedSearch(optimalDist, this->timingBenchmarks, this->maxTimeSearching);
    vector<int> elitistTour = this->elitistAlgorithm->getBestTour();
    double elitistDist = this->elitistAlgorithm->getBestTourDistance();
    for (int i = 0; i < elitistTimes.size() - 1; i++){
        cout << "Elitist found a tour of < " << this->timingBenchmarks[i] << " the optimal in " << elitistTimes[i] << " seconds" <<endl;
    }
    cout << "Elitist found its best tour in " << elitistTimes[elitistTimes.size() - 1] << " seconds" <<endl;
    cout << "Elitist Algorithm found a tour of distance " << elitistDist << " while the optimal distance was " << optimalDist <<endl;
    cout << "The Elitist algorithm got a tour " << elitistDist / optimalDist << " times the optimal" << endl;
}


void ACOTester::compareTestOnce(double optimalDist, double& elitistResult, double& acsResult){
    this->acsAlgorithm->search(this->maxTimeSearching);
    vector<int> acsTour = this->acsAlgorithm->getBestTour();
    double acsDist = this->acsAlgorithm->getBestTourDistance();
    acsResult = acsDist / optimalDist;

    this->elitistAlgorithm->search(this->maxTimeSearching);
    vector<int> elitistTour = this->elitistAlgorithm->getBestTour();
    double elitistDist = this->elitistAlgorithm->getBestTourDistance();
    elitistResult = elitistDist / optimalDist;
}


void ACOTester::compareTestOnceTimed(double optimalDist, double& elitistResult, double& acsResult){
    vector<double> acsTimes = this->acsAlgorithm->timedSearch(optimalDist, this->timingBenchmarks, this->maxTimeSearching);
    vector<int> acsTour = this->acsAlgorithm->getBestTour();
    double acsDist = this->acsAlgorithm->getBestTourDistance();
    acsResult = acsDist / optimalDist;

    vector<double> elitistTimes = this->elitistAlgorithm->timedSearch(optimalDist, this->timingBenchmarks, this->maxTimeSearching);
    vector<int> elitistTour = this->elitistAlgorithm->getBestTour();
    double elitistDist = this->elitistAlgorithm->getBestTourDistance();
    elitistResult = elitistDist / optimalDist;
}


void ACOTester::compareTestManyTimes(double optimalDist){
    double sumElitist = 0;
    double sumACS = 0;
    for (int i = 0; i < numTests; i++){
        double elitistRes;
        double acsRes;
        compareTestOnce(optimalDist, elitistRes, acsRes);
        sumElitist += elitistRes;
        sumACS += acsRes;
    }
    double avgElitistRes = sumElitist / numTests;
    double avgACSRes = sumACS / numTests;
    //TODO: What do we want with these?
    cout << "avgElitistRes = " << avgElitistRes << endl;
    cout << "avgACSRes = " << avgACSRes << endl;
}


vector< pair<double,double> > ACOTester::compareTestManyTimesTimed(double optimalDist){
    vector< pair<double,double> > timesForBoth;
    double sumElitist = 0;
    double sumACS = 0;
    for (int i = 0; i < numTests; i++){
        double elitistRes;
        double acsRes;
        compareTestOnce(optimalDist, elitistRes, acsRes);
        sumElitist += elitistRes;
        sumACS += acsRes;
    }
    double avgElitistRes = sumElitist / numTests;
    double avgACSRes = sumACS / numTests;
    //TODO: What do we want with these?
    cout << "avgElitistRes = " << avgElitistRes << endl;
    cout << "avgACSRes = " << avgACSRes << endl;

    return timesForBoth;
}





