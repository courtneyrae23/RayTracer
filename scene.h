#ifndef __SCENE_H_INCLUDED__   // if x.h hasn't been included yet...
#define __SCENE_H_INCLUDED__   //   #define this so the compiler knows it has been included

#include "camera.h"
#include "light.h"
#include "primitive.h"
#include <vector>
#include <string>

class Scene {
  public:
    Point eye, UL, UR, LL, LR;
    int dimx, dimy;
    Scene (Point* e, Point* ll, Point* ul, Point* lr, Point* ur, int x, int y) {
        eye = *e;
        LL = *ll;
        UL = *ul;
        LR = *lr;
        UR = *ur;
        dimx = x;
        dimy = y;
    }

    Scene () {
        eye = *(new Point(0, 0, 0));
        LL = *(new Point(0, 0, 0));
        UL = *(new Point(0, 0, 0));
        LR = *(new Point(0, 0, 0));
        UR = *(new Point(0, 0, 0));
        dimx = 0;
        dimy = 0;
    }
    void render(std::vector<Light*>, std::vector<Primitive*>, char*);
};

#endif