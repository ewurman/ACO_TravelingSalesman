

#ifndef UTILS_CPP
#define UTILS_CPP



#include <math.h>

typedef struct City {
    double x;
    double y;
    
    double operator- (const City &rightCity) const {
        //Euclidean 2D distance
        return sqrt((x - rightCity.x)*(x - rightCity.x) + (y - rightCity.y)*(y - rightCity.y));
    }
} City;


#endif