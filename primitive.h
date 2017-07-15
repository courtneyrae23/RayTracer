#ifndef __PRIM_H_INCLUDED__   // if x.h hasn't been included yet...
#define __PRIM_H_INCLUDED__

#include <iostream>
#include "shapes.h"
#include "material.h"
#include "intersection.h"
#include "transformation.h"
 
using namespace std;
 
class Intersection;
// Base class
class Primitive  {
	public:
	    // pure virtual function providing interface framework.
	    virtual bool intersect(Ray&, float&, Intersection&) = 0;
	    virtual bool intersectP(Ray&) = 0;
	    virtual void getBRDF(LocalGeo&, BRDF&) = 0;
};
 
// Derived classes
class GeometricPrimitive: public Primitive {
	public:
		Transformation objToWorld, worldToObj;
		Shape* shape;
		Material* mat;
		GeometricPrimitive(Transformation oTw, Transformation wTo, Shape* s, Material* m) {
			objToWorld = oTw;
			worldToObj = wTo;
			shape = s;
			mat = m;
		}
		GeometricPrimitive() {
			objToWorld = *(new Transformation());
			worldToObj = *(new Transformation());
			shape = new Sphere(*(new Point(0.0, 0.0, 0.0)), 0.0);
			mat = new Material();
		}
	    bool intersect(Ray&, float&, Intersection&);
	    bool intersectP(Ray&);
	    void getBRDF(LocalGeo&, BRDF&);
};

class AggregatePrimitive: public Primitive {
	public:
		std::vector<Primitive*> primitives;
		AggregatePrimitive(std::vector<Primitive*> list) {
			primitives = list;
		}
	    bool intersect(Ray&, float&, Intersection&);
	    bool intersectP(Ray&);
	    void getBRDF(LocalGeo&, BRDF&);
};

#endif