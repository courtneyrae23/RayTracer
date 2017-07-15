// Sampler.cpp
#include "sampler.h"
#include <iostream>
using namespace std;

bool Sampler::generateSample (Sample* sample) {
    if (currX == dimx-1) {
        if (currY == dimy-1) {
            return false;
        } else {
            currY += 1;
        }
    } else {
        if (currY == dimy-1) {
            currX += 1;
            currY = 0;
        } else {
            currY += 1;
        }
    }

    sample->x = currX;
    sample->y = currY;
    return true;
}