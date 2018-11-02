

#ifndef UTILS_CPP
#define UTILS_CPP



#include <math.h>

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
        return id == rightCity.id && x = rightCity.x && y == rightCity.y;
    }




} City;


#endif