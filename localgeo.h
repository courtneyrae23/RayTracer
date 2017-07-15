#ifndef __LG_H_INCLUDED__
#define __LG_H_INCLUDED__


#include <math.h>
#include "cartesian.h"

class LocalGeo{
  public:
  	Point pos;
    Normal norm;
    LocalGeo(Point p, Normal n) {
    	pos = p;
    	norm = n;
    }
    LocalGeo() {
    	pos = *(new Point(0.0, 0.0, 0.0));
    	norm = *(new Normal(0.0, 0.0, 0.0));
    }
};

#endif