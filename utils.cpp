

#ifndef UTILS_CPP
#define UTILS_CPP



#include <math.h>
#include <iostream>
#include <vector>

using namespace std;


void printvect(vector<int> vect) {
    cout << "tour by city id: ";
    for (int i =0; i<vect.size(); i++) {
        cout << vect[i] << " ";
    }
    cout << endl;
}

double randomDoubleInRange(double fMin, double fMax)
{
    double f = (double)rand() / RAND_MAX;
    return fMin + f * (fMax - fMin);
}


#endif

