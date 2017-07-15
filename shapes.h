#ifndef __SHAPES_H_INCLUDED__
#define __SHAPES_H_INCLUDED__


#include "cartesian.h"
#include "localgeo.h"

class Shape{
	public:
		virtual bool intersect(Ray&, float&, LocalGeo&) = 0;
		virtual bool intersectP(Ray&) = 0;
};

class Triangle : public Shape {
	public:
		Point v1, v2, v3;
		Normal norm;
		Triangle(Point* x, Point* y, Point* z) {
			v1 = *x;
			v2 = *y;
			v3 = *z;
			norm = ((v2-v1).cross_product(v3-v1)).normalize();
		}
		bool intersect(Ray&, float&, LocalGeo&);
		bool intersectP(Ray&);
};

class Sphere : public Shape {
	public:
		Point center;
		float radius;
		Sphere(Point cent, float rad) {
			center = cent;
			radius = rad;
		}
		bool intersect(Ray&, float&, LocalGeo&);
		bool intersectP(Ray&);
};

#endif