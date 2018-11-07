/*
 * TSP.cpp
 * Created by Erik Wurman and Ian Squiers
 */

#include "TSP.hpp"
#include <fstream>
#include <sstream>
#include <iostream>
#include <string.h>
#include <stdio.h>

using namespace std;

string EUC_2D = "EUC_2D";
string EDGE_WEIGHT_TYPE = "EDGE_WEIGHT_TYPE";
string NODE_COORD_SECTION = "NODE_COORD_SECTION";
string END_OF_FILE1 = "EOF";


TSP::TSP(){
    this->cities = *new std::vector<City>();
    this->numCities = 0;
}


TSP::TSP(string filename) {
    //validate the file
    this->cities = parseFileForCities(filename);
    this->numCities = (int)cities.size();
}

vector<City> TSP::parseFileForCities(string filename){
    ifstream infile(filename);
    string line;
    bool foundFormatType = false;
    bool foundNodeCoordSection = false;
    vector<City> cities;
    while (getline(infile, line)) { 

        if (!line.substr(0,3).compare(END_OF_FILE1)) {
            return cities;
        }
        // EDGE_WEIGHT_TYPE : EUC_2D is the line we want
        // then NODE_COORD_SECTION
        int dataType = (int)line.find(EDGE_WEIGHT_TYPE);
        if (dataType != std::string::npos){
            if (DEBUG_ON)
                cout << line << endl;

            line = line.substr(dataType + EDGE_WEIGHT_TYPE.length());
            size_t typeIndex = line.find_first_not_of(" :");
            string type = line.substr(typeIndex);
            if (DEBUG_ON)
                cout << type <<endl;
            if (!type.compare(EUC_2D)){
                foundFormatType = true;
                if (DEBUG_ON)
                    cout << "Yay! found the correct Format Type line" << endl;
            }
            else {
                cout << "Error: Wrong EDGE_WEIGHT_TYPE for file " << filename << endl;
                return cities;
            }
        }

        if (foundNodeCoordSection) {
            size_t firstNum = line.find_first_not_of(" ");
            line = line.substr(firstNum);
            size_t firstspace = line.find(" "); 
            // skip city num?
            int cityNum = stoi(line.substr(0,firstspace));


            line = line.substr(firstspace);
            int firstCoor = (int)line.find_first_not_of(" ");
            line = line.substr(firstCoor);
            // Now we should only have firstCoor space secondCoor as the line

            size_t spaceBetween = line.find(" ");
            double xCoor = stod(line.substr(0,spaceBetween));

            line = line.substr(spaceBetween);
            double yCoor = stod(line);

            City newCity;
            newCity.id = cityNum - 1; // we want them to be 0 indexed
            newCity.x = xCoor;
            newCity.y = yCoor;
            cities.push_back(newCity);
        }


        if (foundFormatType){
            int nodeSection = (int)line.find(NODE_COORD_SECTION);
            if (nodeSection != std::string::npos){
                if (DEBUG_ON)
                    cout << line << endl;
                string startOfLine = line.substr(nodeSection, NODE_COORD_SECTION.length());
                if (!startOfLine.compare(NODE_COORD_SECTION)){
                    foundNodeCoordSection = true;
                    if (DEBUG_ON)
                        cout << "Found the Node Coord Section" <<endl;
                }
            }
        }   

    }
    return cities;
}




void TSP::printCities(){
    cout << "There are " << this->numCities << " cities" << endl;
    for (int i = 0; i < this->numCities; i++){     
        cout << "City " << this->cities[i].id << " at " << this->cities[i].x << ", " << this->cities[i].y << endl;
    }
}



