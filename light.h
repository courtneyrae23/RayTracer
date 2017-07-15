#ifndef __LIGHT_H_INCLUDED__   // if x.h hasn't been included yet...
#define __LIGHT_H_INCLUDED__

#include "BRDF.h"
#include "localgeo.h"

class Light {
    public:
        Point location;
        Color color;
        int falloff;
        bool point;
        bool directional;
        bool ambient; 
        Light (Point l, Color c, int f, bool p, bool d, bool a) {
            if (p) {
                location = l;
                color = c;
                point = true;
                directional = false;
                falloff = f;
                ambient = false;
            } else if (d) {
                Point* loc = new Point(l.x * -1, l.y * -1, l.z * -1);
                location = *loc;
                color = c;
                point = false;
                falloff = 0;
                directional = true;
                ambient = false;
            } else if (a) {
                Point* loc = new Point();
                location = *loc;
                color = c;
                point = false;
                falloff = 0;
                directional = false;
                ambient = true;
            }
        }
        void generateLightRay(LocalGeo&, Ray&, Color&);
};

#endif