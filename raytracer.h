#ifndef __RAYTRACE_H_INCLUDED__   // if x.h hasn't been included yet...
#define __RAYTRACE_H_INCLUDED__

#include "intersection.h"
#include "light.h"
#include <vector>
#include "primitive.h"

class RayTracer {
	public:
		std::vector<Light*> lights;
		AggregatePrimitive* primitives;
		RayTracer(std::vector<Light*> l, std::vector<Primitive*> p) {
			lights = l;
			primitives = new AggregatePrimitive(p);
		}
		void trace(Ray&, int, Color&);
		Color shading(LocalGeo, BRDF, Ray, Color, Ray);
		Ray createReflectRay(LocalGeo, Ray);
};

#endif