#ifndef __BRDF_H_INCLUDED__   // if x.h hasn't been included yet...
#define __BRDF_H_INCLUDED__


#include "color.h"
class BRDF {
    public:
        Color ka, kd, ks, kr;
        float sp;
        BRDF(Color a, Color d, Color s, Color r, float p) {
            ka = a;
            kd = d;
            ks = s;
            kr = r;
            sp = p;
        }
        BRDF() {
            Color* a = new Color(0.0, 0.0, 0.0);
            Color* d = new Color(0.0, 0.0, 0.0);
            Color* s = new Color(0.0, 0.0, 0.0);
            Color* r = new Color(0.0, 0.0, 0.0);
            float p = 1.0;

            ka = *a;
            kd = *d;
            ks = *s;
            kr = *r;
            sp = p;
        }
};

#endif