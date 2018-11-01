/*
 * TSP.hpp
 * Created by Erik Wurman and Ian Squiers
 */



#ifndef TSP_hpp
#define TSP_hpp

#include <vector>
#include <string>
#include "utils.cpp"

using namespace std;

class TSP {

    private:
        int numCities;


    public:
        vector<City> cities;
        // Do we need something to represent Edges, for pheremones later?
        TSP();
        TSP(string fileName);
        vector<City> parseFileForCities(char* filename);
};

#endif
