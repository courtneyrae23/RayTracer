#include "sample.h"

class Sampler {
  public:
    int dimx, dimy, currX, currY;
    Sampler(int x, int y) {
        dimx = x;
        dimy = y;
        currX = 0;
        currY = -1;
    }
    bool generateSample(Sample*);
};