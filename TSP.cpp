/*
 * TSP.cpp
 * Created by Erik Wurman and Ian Squiers
 */

#include "TSP.hpp"
#include <fstream>
#include <sstream>
#include <iostream>

string COORD_DISPLAY = "COORD_DISPLAY";
string DISPLAY_DATA_TYPE = "DISPLAY_DATA_TYPE: ";


TSP::TSP(){
    this->cities = *new std::vector<City>();
    this->numCities = 0
}


TSP::TSP(string filename){
    //validate the file
}

vector<City> TSP::parseFileForCities(char* filename){
    ifstream infile(filename);
    string line;
    bool foundFormatType = false;
    vector<City> cities;
    while (getline(infile, line)) {

        if (!strcmp(line.substr(0,3),"EOF")){
            return cities;
        }
        //DISPLAY_DATA_TYPE: COORD_DISPLAY is the line we want
        int dataType = line.find(DISPLAY_DATA_TYPE);
        if (dataType != std::string::npos){
            string type = line.substr(dataType);
            if (!strcmp(type, COORD_DISPLAY)){
                foundFormatType = true;
            }
            else {
                cout << "Error: Wrong DISPLAY_DATA_TYPE for file " << filename << endl;
                return cities;
            }
        }
        if (foundFormatType) {
            firstNum = line.find_first_not_of(" ");
            line = line.substr(firstNum);
            firstspace = line.find(" ");
            //subline = subline.substr(space);
        }
    }
}