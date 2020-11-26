#ifndef HELPER_H__
#define HELPER_H__

#include <cmath>

namespace Helper {
    inline int findMagnitudeOfNumber(int num) {
        if(num < 0) {
            return -1;
        } else if(num < 10) {
            return 1;
        } else if(num < 100) {
            return 2;
        } else if(num < 1000) {
            return 3;
        } else if(num < 10000) {
            return 4;
        }
        return 5;
    }

    inline double getDistance(double x1, double y1, double x2, double y2) {
        return sqrt(pow(x1 - x2, 2) + pow(y1 - y2, 2));
    }
}


#endif