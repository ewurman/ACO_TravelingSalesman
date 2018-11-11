/*
 * Main.cpp created by Erik Wurman and Ian Squiers.
 * 11/4/19
 */


#include <iostream>
#include "ACOTester.hpp"
#include "ACO.hpp"
#include "TSP.hpp"
#include "ACS.hpp"
#include "Elitist.hpp"
#include "utils.hpp"
#include <map>
#include <fstream>
//#include <iostream>
//#include "ACOTester.cpp"
//#include "ACO.cpp"
//#include "TSP.cpp"
//#include "ACS.cpp"
//#include "Elitist.cpp"
//#include "utils.cpp"
//#include <map>
//#include <fstream>

int main(int argc, const char * argv[]) {

    srand(time(0));
    if (argc == 1) {

        bool recordingToFile = true;
        bool initialTesting = false;

        std::map<string, double> tspProblemsMap;
        //tspProblemsMap["u574.tsp"] = 36905;
        //tspProblemsMap["u1060.tsp"] = 224094;
        tspProblemsMap["vm1748.tsp"] = 336556;
        tspProblemsMap["u2152.tsp"] = 64253;
        tspProblemsMap["pcb3038.tsp"] = 137694;
        tspProblemsMap["fnl4461.tsp"] = 182566;
        tspProblemsMap["rl5915.tsp"] = 565530;
        
        
        int ants = 15;
        double alphas[] = {1};
        double betas[] = {3.5,2,5};
        double rhos[] = {0.5, 0.1};
        double q_naughts[] = {0.7, 0.8, 0.9};
        double epsilons[] = {0.1};
        int iterations = 10000;


        double testAlpha = 1;
        double testBeta = 5;
        double testRho = 0.1;
        double test_q_0 = 0.7;
        double testEpsilon = 0.1;
        int testIterations = 10000;


        /* First we want to find the parameters that lead to good solutions on a small probelem for each algorithm
         * Then we want to use these parameters to compare the two algorithms on larger files
         */

        //This code here is for finding good parameters
        if (recordingToFile) {
                string header = "";
                string notFound = "-1";

            string elitistFilename = "/Users/iansquiers/Desktop/NI/ACO_TravelingSalesman/OutputFiles/elitist4461.csv";
                //string elitistFilename = "u574_Elitist.csv";
                fstream elitistFile;
                elitistFile.open(elitistFilename, ios::out);

                string acsFilename = "/Users/iansquiers/Desktop/NI/ACO_TravelingSalesman/OutputFiles/ACS4461.csv";
                //string acsFilename = "u574_ACS.csv";
                fstream acsFile;
                acsFile.open(acsFilename, ios::out);

                //TSP* tsp = new TSP("TestFiles/u574.tsp");
                //TSP *tsp = new TSP("TestFiles/a280.tsp");
                TSP *tsp = new TSP("/Users/iansquiers/Desktop/NI/ACO_TravelingSalesman/TestFiles/fnl4461.tsp");
                //double optimalLength = 36905;
                //double optimalLength = 2579;
                //double optimalLength = 7432.85;64253
                double optimalLength = 182566;
                
                //ACOTester baseACOTester = *new ACOTester(*tsp, ants, iterations, alphas[0], betas[0], rhos[0], tsp->numCities, q_naughts[0], epsilons[0]);

                
                if (initialTesting){

                    for(int k = 0; k<7; k++){
                        cout << "Starting All tests for k =" << k << endl;
                        ACOTester* acoTester;
                        if (k < 3) {
                            acoTester= new ACOTester(tsp, ants, iterations, alphas[0], betas[k], rhos[0], tsp->numCities, q_naughts[0], epsilons[0]);
                            if (k == 0){
                                double firstBenchmark = acoTester->timingBenchmarks[0];
                                header = to_string(firstBenchmark) + "xOptimal";
                                for (int i = 1; i < acoTester->timingBenchmarks.size(); i++){
                                    header += "," + to_string(acoTester->timingBenchmarks[i]) + "xOptimal";
                                }
                                header += ",BestFoundIn,BestResultOptimality";
                                elitistFile << header << endl;
                                acsFile << header << endl;

                                elitistFile << "#Baseline:"<<endl;
                                elitistFile << "#alpha=" << alphas[0] <<",beta="<<betas[0]<<",rho="<<rhos[0]<<",numCities="<<tsp->numCities<<",elitism="<<tsp->numCities<<endl;
                                acsFile << "#Baseline:"<<endl;
                                acsFile << "#alpha=" << alphas[0] <<",beta="<<betas[0]<<",rho="<<rhos[0]<<",numCities="<<tsp->numCities<<",q_0="<<q_naughts[0]<<",epsilon="<<epsilons[0]<<endl;
                            }
                            else{
                                elitistFile << "#alpha=" << alphas[0] <<",beta="<<betas[k]<<",rho="<<rhos[0]<<",numCities="<<tsp->numCities<<",elitism="<<tsp->numCities<<endl;
                                acsFile << "#alpha=" << alphas[0] <<",beta="<<betas[k]<<",rho="<<rhos[0]<<",numCities="<<tsp->numCities<<",q_0="<<q_naughts[0]<<",epsilon="<<epsilons[0]<<endl;
                            }

                        }
                        else if (k == 3){
                            acoTester= new ACOTester(tsp, ants, iterations, alphas[0], betas[0], rhos[1], tsp->numCities, q_naughts[0], epsilons[0]);   
                            elitistFile << "#alpha=" << alphas[0] <<",beta="<<betas[0]<<",rho="<<rhos[1]<<",numCities="<<tsp->numCities<<",elitism="<<tsp->numCities<<endl;
                            acsFile << "#alpha=" << alphas[0] <<",beta="<<betas[0]<<",rho="<<rhos[1]<<",numCities="<<tsp->numCities<<",q_0="<<q_naughts[0]<<",epsilon="<<epsilons[0]<<endl;
                            
                        }
                        else if (k == 4){
                            acoTester= new ACOTester(tsp, ants, iterations, alphas[0], betas[2], rhos[1], tsp->numCities, q_naughts[0], epsilons[0]);   
                            elitistFile << "#alpha=" << alphas[0] <<",beta="<<betas[2]<<",rho="<<rhos[1]<<",numCities="<<tsp->numCities<<",elitism="<<tsp->numCities<<endl;
                            acsFile << "#alpha=" << alphas[0] <<",beta="<<betas[2]<<",rho="<<rhos[1]<<",numCities="<<tsp->numCities<<",q_0="<<q_naughts[0]<<",epsilon="<<epsilons[0]<<endl;
                            
                        }
                        else{
                            acoTester= new ACOTester(tsp, ants, iterations, alphas[0], betas[0], rhos[0], tsp->numCities, q_naughts[k%3], epsilons[0]);
                            elitistFile << "#alpha=" << alphas[0] <<",beta="<<betas[0]<<",rho="<<rhos[0]<<",numCities="<<tsp->numCities<<",elitism="<<tsp->numCities<<endl;
                            acsFile << "#alpha=" << alphas[0] <<",beta="<<betas[0]<<",rho="<<rhos[0]<<",numCities="<<tsp->numCities<<",q_0="<<q_naughts[k%3]<<",epsilon="<<epsilons[0]<<endl;
                        }

                        

                        for (int i = 0; i < acoTester->numTests; i++){
                            clock_t startTime = clock();
                            double elitistRes = -1;
                            double acsRes = -1;
                            pair< vector<double>, vector<double> > timesForBoth = acoTester->compareTestOnceTimed(optimalLength, elitistRes, acsRes);
                            //pair< vector<double>, vector<double> > timesForBoth = acoTester->compareTestManyTimesTimed(optimalLength);
                            clock_t endTime = clock();
                            acoTester->resetAlgorithms();

                            int numBenchmarks = acoTester->timingBenchmarks.size();
                            elitistFile << timesForBoth.first[0]<< ":" << timesForBoth.first[numBenchmarks+1];
                            acsFile << timesForBoth.second[0] << ":" << timesForBoth.second[numBenchmarks+1];
                            for (int j = 1; j < numBenchmarks; j++){
                                // ELITIST FILE
                                //if (i < timesForBoth.first.size()){
                                elitistFile << "," << timesForBoth.first[j] << ":" << timesForBoth.first[j+numBenchmarks+1];
                                acsFile << "," << timesForBoth.second[j] << ":" << timesForBoth.second[j+numBenchmarks+1];

                            }

                            elitistFile << "," << timesForBoth.first[acoTester->timingBenchmarks.size()] << "," << elitistRes << endl;
                            acsFile << "," << timesForBoth.second[acoTester->timingBenchmarks.size()] << "," << acsRes << endl;

                            for (int j = 0; j < acoTester->timingBenchmarks.size(); j++){
                                cout << acoTester->timingBenchmarks[j] << " Elitist: ";
                                cout << timesForBoth.first[j] <<":"<< timesForBoth.first[j+numBenchmarks+1] << " ";
                                cout << "ACS: ";
                                cout << timesForBoth.second[j] <<":"<< timesForBoth.second[j+numBenchmarks+1] << " ";
                                cout << endl;
                            }
                            cout << "Total Time " << (double) (endTime - startTime ) / (double)CLOCKS_PER_SEC << endl;

                            timesForBoth.first.clear();
                            timesForBoth.second.clear();
                        }
                        delete (acoTester);
                    }

                }
                else {
                    ACOTester* acoTester = new ACOTester(tsp, ants, testIterations, testAlpha, testBeta, testRho, tsp->numCities, test_q_0, testEpsilon);
                    double firstBenchmark = acoTester->timingBenchmarks[0];
                    header = to_string(firstBenchmark) + "xOptimal";
                    for (int i = 1; i < acoTester->timingBenchmarks.size(); i++){
                        header += "," + to_string(acoTester->timingBenchmarks[i]) + "xOptimal";
                    }
                    header += ",BestFoundIn,BestResultOptimality";
                    elitistFile << header << endl;
                    acsFile << header << endl;

                    elitistFile << "#Test parameters:"<<endl;
                    elitistFile << "#alpha=" << testAlpha <<",beta="<<testBeta<<",rho="<<testRho<<",numCities="<<tsp->numCities<<",elitism="<<tsp->numCities<<endl;
                    acsFile << "#Baseline:"<<endl;
                    acsFile << "#alpha=" << testAlpha <<",beta="<<testBeta<<",rho="<<testRho<<",numCities="<<tsp->numCities<<",q_0="<<test_q_0<<",epsilon="<<testEpsilon<<endl;
                    
                    for (int i = 0; i < acoTester->numTests; i++){
                        clock_t startTime = clock();
                        double elitistRes = -1;
                        double acsRes = -1;
                        pair< vector<double>, vector<double> > timesForBoth = acoTester->compareTestOnceTimed(optimalLength, elitistRes, acsRes);
                        //pair< vector<double>, vector<double> > timesForBoth = acoTester->compareTestManyTimesTimed(optimalLength);
                        clock_t endTime = clock();
                        acoTester->resetAlgorithms();

                        int numBenchmarks = acoTester->timingBenchmarks.size();
                        elitistFile << timesForBoth.first[0]<< ":" << timesForBoth.first[numBenchmarks+1];
                        acsFile << timesForBoth.second[0] << ":" << timesForBoth.second[numBenchmarks+1];
                        for (int j = 1; j < numBenchmarks; j++){
                            // ELITIST FILE
                            //if (i < timesForBoth.first.size()){
                            elitistFile << "," << timesForBoth.first[j] << ":" << timesForBoth.first[j+numBenchmarks+1];
                            acsFile << "," << timesForBoth.second[j] << ":" << timesForBoth.second[j+numBenchmarks+1];

                        }

                        elitistFile << "," << timesForBoth.first[acoTester->timingBenchmarks.size()] << "," << elitistRes << endl;
                        acsFile << "," << timesForBoth.second[acoTester->timingBenchmarks.size()] << "," << acsRes << endl;

                        for (int j = 0; j < acoTester->timingBenchmarks.size(); j++){
                            cout << acoTester->timingBenchmarks[j] << " Elitist: ";
                            cout << timesForBoth.first[j] <<":"<< timesForBoth.first[j+numBenchmarks+1] << " ";
                            cout << "ACS: ";
                            cout << timesForBoth.second[j] <<":"<< timesForBoth.second[j+numBenchmarks+1] << " ";
                            cout << endl;
                        }
                        cout << "Total Time " << (double) (endTime - startTime ) / (double)CLOCKS_PER_SEC << endl;

                        timesForBoth.first.clear();
                        timesForBoth.second.clear();
                    }
                    delete (acoTester);
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
    
        ACOTester acoTester = *new ACOTester(tsp, 30, 10000, 1, 3, 0.5, tsp->numCities, 0.7, 0.1);
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


