//
//  Header.h
//  ACO
//
//  Created by Ian Squiers on 11/1/18.
//  Copyright © 2018 Ian Squiers. All rights reserved.
//

#ifndef Header_h
#define Header_h

#include <math.h>
#include <vector>

using namespace std;

typedef struct City {
    double x;
    double y;
    int id;
    
    double operator- (const City &rightCity) const {
        //Euclidean 2D distance
        if (id == rightCity.id){
            return 0;
        }
        return sqrt((x - rightCity.x)*(x - rightCity.x) + (y - rightCity.y)*(y - rightCity.y));
    }
    
    double operator== (const City &rightCity) const {
        return id == rightCity.id && x == rightCity.x && y == rightCity.y;
    }
    
    
    
    
} City;void printvect(vector<int> vect);
double randomDoubleInRange(double fMin, double fMax);
#endif /* Header_h */
