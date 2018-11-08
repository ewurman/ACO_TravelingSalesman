/*
 * Main.cpp created by Erik Wurman and Ian Squiers.
 * 11/4/19
 */


//#include <iostream>
//#include "ACOTester.hpp"
//#include "ACO.hpp"
//#include "TSP.hpp"
//#include "ACS.hpp"
//#include "Elitist.hpp"
//#include "utils.hpp"
//#include <map>
//#include <fstream>
#include <iostream>
#include "ACOTester.cpp"
#include "ACO.cpp"
#include "TSP.cpp"
#include "ACS.cpp"
#include "Elitist.cpp"
#include "utils.cpp"
#include <map>
#include <fstream>

int main(int argc, const char * argv[]) {

    srand(time(0));
    if (argc == 1) {

        bool recordingToFile = true;

        std::map<string, double> tspProblemsMap;
        //tspProblemsMap["u574.tsp"] = 36905;
        //tspProblemsMap["u1060.tsp"] = 224094;
        //tspProblemsMap["vm1748.tsp"] = 336556;
        tspProblemsMap["u2152.tsp"] = 64253;
        tspProblemsMap["pcb3038.tsp"] = 137694;
        tspProblemsMap["fnl4461.tsp"] = 182566;
        tspProblemsMap["rl5915.tsp"] = 565530;
        
        int ants = 15;
        double alphas[] = {1};
        double betas[] = {2,3.5,5};
        double rhos[] = {0.1, 0.5};
        double q_naughts[] = {0.7, 0.9};
        double epsilons[] = {0.1};
        int iterations = 1000;

        /* First we want to find the parameters that lead to good solutions on a small probelem for each algorithm
         * Then we want to use these parameters to compare the two algorithms on larger files
         */

        //This code here is for finding good parameters
        if (recordingToFile) {
                string header = "";
                string notFound = "-1";

                string elitistFilename = "a280_Elitist.csv";
                fstream elitistFile;
                elitistFile.open(elitistFilename, ios::out);

                string acsFilename = "a280_ACS.csv";
                fstream acsFile;
                acsFile.open(acsFilename, ios::out);

                //TSP *tsp = new TSP("TestFiles/u574.tsp");
                TSP *tsp = new TSP("TestFiles/a280.tsp");
                //TSP *tsp = new TSP("TestFiles/berlin52.tsp");
                //double optimalLength = 36905;
                double optimalLength = 2579;
                //double optimalLength = 7432.85;
                ACOTester acoTester = *new ACOTester(*tsp, ants, iterations, alphas[0], betas[1], rhos[1], tsp->numCities, q_naughts[0], epsilons[0]);

                double firstBenchmark = acoTester.timingBenchmarks[0];
                header = to_string(firstBenchmark);
                for (int i = 1; i < acoTester.timingBenchmarks.size(); i++){
                    header += "," + to_string(acoTester.timingBenchmarks[i]) + "xOptimal";
                }
                header += ",BestFoundIn,BestResultOptimality";
                elitistFile << header << endl;
                acsFile << header << endl;

                

                for (int i = 0; i < acoTester.numTests; i++){
                    clock_t startTime = clock();
                    double elitistRes = -1;
                    double acsRes = -1;
                    pair< vector<double>, vector<double> > timesForBoth = acoTester.compareTestOnceTimed(optimalLength, elitistRes, acsRes);
                    //pair< vector<double>, vector<double> > timesForBoth = acoTester.compareTestManyTimesTimed(optimalLength);
                    clock_t endTime = clock();
                    acoTester.resetAlgorithms();

                    elitistFile << timesForBoth.first[0];
                    acsFile << timesForBoth.second[0];
                    for (int j = 1; j < acoTester.timingBenchmarks.size(); j++){
                        // ELITIST FILE
                        //if (i < timesForBoth.first.size()){
                        elitistFile << "," << timesForBoth.first[j];
                        acsFile << "," << timesForBoth.second[j];

                    }

                    elitistFile << "," << timesForBoth.first[acoTester.timingBenchmarks.size()] << "," << elitistRes << endl;
                    acsFile << "," << timesForBoth.second[acoTester.timingBenchmarks.size()] << "," << acsRes << endl;

                    for (int j = 0; j < acoTester.timingBenchmarks.size(); j++){
                        cout << acoTester.timingBenchmarks[j] << " Elitist: ";
                        cout << timesForBoth.first[j] << " ";
                        cout << "ACS: ";
                        cout << timesForBoth.second[j] << " ";
                        cout << endl;
                    }
                    cout << "Total Time " << (double) (endTime - startTime ) / (double)CLOCKS_PER_SEC << endl;

                    timesForBoth.first.clear();
                    timesForBoth.second.clear();
                }
                elitistFile.close();
                acsFile.close();
                
        }

        /*
        map<string, double>::iterator it;
        for (it = tspProblemsMap.begin(); it != tspProblemsMap.end(); it++){
            string filename = it->first;
            double optimalLength = it->second;
            TSP *tsp = new TSP(string("/Users/iansquiers/Desktop/NI/ACO_TravelingSalesman/TestFiles/") + filename);
            ACOTester acoTester = *new ACOTester(*tsp, ants, iterations, alphas[0], betas[1], rhos[1], tsp->numCities, q_naughts[0], epsilons[0]);

            //Now run tests somehow
            cout << "Testing on " << filename << " which has optimal distance of " << optimalLength << endl;
            acoTester.compareTestManyTimes(optimalLength);
        }
        */
    }
    
    else if (argc != 3){
        cout << "Proper arguments are <TSP_filename> <optimalTour_filename> to run one comparisonTest" <<endl;
        cout << "To run all tests, have no arguments" << endl;
        exit(0);
    }
    
    else if (argc == 3) {
        const char* tspfilename = argv[1];
        const char* optimalTour_filename = argv[2];
        TSP *tsp = new TSP(tspfilename);
    
        ACOTester acoTester = *new ACOTester(*tsp, 30, 1000, 1, 3, 0.5, tsp->numCities, 0.7, 0.1);
        acoTester.basicTestTimed(optimalTour_filename);
        //acoTester.basicTest(optimalTour_filename);
    }

    // (TSP tsp, int numAnts, int maxIterations, double alpha, double beta, double rho, double q_naught, double tau_naught, double epsilon)

    /*
    const char * topologytype = argv[1];
    int num_particles = atoi(argv[2]);
    int iterations = atoi(argv[3]);
    const char * func = argv[4];
    const int dimensions = atoi(argv[5]);
    */
}


