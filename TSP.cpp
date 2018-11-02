/*
 * TSP.cpp
 * Created by Erik Wurman and Ian Squiers
 */

#include "TSP.hpp"
#include <fstream>
#include <sstream>
#include <iostream>

string EUC_2D = "EUC_2D";
string EDGE_WEIGHT_TYPE = "EDGE_WEIGHT_TYPE : ";
string NODE_COORD_SECTION = "NODE_COORD_SECTION";


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
    bool foundNodeCoordSection = false;
    vector<City> cities;
    while (getline(infile, line)) {

        if (!strcmp(line.substr(0,3),"EOF")){
            return cities;
        }
        // EDGE_WEIGHT_TYPE : EUC_2D is the line we want
        // then NODE_COORD_SECTION
        int dataType = line.find(EDGE_WEIGHT_TYPE);
        if (dataType != std::string::npos){
            string type = line.substr(dataType);
            if (!strcmp(type, EUC_2D)){
                foundFormatType = true;
            }
            else {
                cout << "Error: Wrong EDGE_WEIGHT_TYPE for file " << filename << endl;
                return cities;
            }
        }

        if (foundFormatType){
            int nodeSection = line.find(NODE_COORD_SECTION);
            if (nodeSection != std::string::npos){
                string startOfLine = line.substr(nodeSection, NODE_COORD_SECTION.length());
                if (!strcmp(startOfLine, NODE_COORD_SECTION)){
                    foundNodeCoordSection = true;
                }
            }
        }   

        if (foundNodeCoordSection) {
            int firstNum = line.find_first_not_of(" ");
            line = line.substr(firstNum);
            int firstspace = line.find(" "); 
            // skip city num?
            int cityNum = stoi(line.substr(0,firstspace));


            line = line.substr(space);
            int firstCoor = line.find_first_not_of(" ");
            line = line.substr(firstCoor);
            // Now we should only have firstCoor space secondCoor as the line
        }
    }
}