#include "localgeo.h"
#include "sampler.h"
class Camera {
    public:
    	Point eye, UL, UR, LL, LR;
    	int dimx, dimy;
        Camera (Point e, Point ll, Point ul, Point lr, Point ur, int x, int y) {
        eye = e;
        LL = ll;
        UL = ul;
        LR = lr;
        UR = ur;
        dimx = x;
        dimy = y;
    }
        void generateRay(Sample&, Ray*);
};