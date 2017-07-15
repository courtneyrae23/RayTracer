#include "light.h"
#include <float.h>
#include <iostream>
using namespace std;

void Light::generateLightRay(LocalGeo& local, Ray& lray, Color& lcolor) {
    if (ambient) {
        return;
    } else if (point) {
        lray.tmax = 1;
        float r = (location - local.pos).length();
        if (falloff == 2) {
            lcolor = color*(1.0/(r*r));
        } else if (falloff == 1) {
            lcolor = color*(1.0/r);
        } else {
            lcolor = color;
        }
        lray.dir = (location - local.pos);
    } else if (directional) {
        //cout << "WOOOOOOOO" << endl;
        lray.dir = location - *(new Point(0.0, 0.0, 0.0));
        lray.tmax = FLT_MAX;
        lcolor = color;
    } 

    lray.pos = local.pos;
    lray.tmin = 0.0001;
}