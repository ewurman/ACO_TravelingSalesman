/*
 * TSP.hpp
 * Created by Erik Wurman and Ian Squiers
 */



#ifndef TSP_hpp
#define TSP_hpp

#include <vector>
#include <string.h>
#include "utils.hpp"


using namespace std;

class TSP {

    private:
        bool DEBUG_ON = true;

    public:

        vector<City> cities;
        int numCities;
        // Do we need something to represent Edges, for pheremones later?
        TSP();
        TSP(string fileName);
        vector<City> parseFileForCities(string filename);
        void printCities();
};

#endif
