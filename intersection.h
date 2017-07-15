#ifndef __IN_H_INCLUDED__   // if x.h hasn't been included yet...
#define __IN_H_INCLUDED__

#include "localgeo.h"
#include "primitive.h"

class GeometricPrimitive;

class Intersection {
	public:
		LocalGeo local;
		GeometricPrimitive* primitive;
		Intersection (LocalGeo l, GeometricPrimitive* p) {
			local = l;
			primitive = p;
		}
};

#endif