#include <math.h>
#include "localgeo.h"
#include "shapes.h"
#include <iostream>

using namespace std;

inline float sqr(float x) { return x*x; };

bool Triangle::intersect(Ray& ray, float& thit, LocalGeo& local){
	// Computed using Cramer's rule and formula from the book
	float a, b, c, d, e, f, g, h, i, j, k, l;
	a = v1.x-v2.x;
	b = v1.y-v2.y;
	c = v1.z-v2.z;
	d = v1.x-v3.x;
	e = v1.y-v3.y;
	f = v1.z-v3.z;
	g = ray.dir.x;
	h = ray.dir.y;
	i = ray.dir.z;
	j = v1.x-ray.pos.x;
	k = v1.y-ray.pos.y;
	l = v1.z-ray.pos.z;

	float M = a*(e*i-h*f) + b*(g*f-d*i) + c*(d*h-e*g);
	thit = -1*((f*(a*k-j*b) + e*(j*c-a*l) + d*(b*l-k*c))/M);
	if (thit < ray.tmin || thit > ray.tmax) {
		return false;
	} 
	float gamma = (i*(a*k-j*b) + h*(j*c-a*l) + g*(b*l-k*c))/M;
	if (gamma < 0 || gamma > 1) {
		return false;
	}
	float beta = (j*(e*i-h*f) + k*(g*f-d*i) + l*(d*h-e*g))/M;
	if (beta < 0 || beta > (1 - gamma)) {
		return false;
	}

	local.pos = ray.pos + (ray.dir * thit);
	local.norm = norm;
	return true;
};

bool Triangle::intersectP(Ray& ray){
  LocalGeo local;
  float thit;
  return Triangle::intersect(ray, thit, local);
};

bool Sphere::intersect(Ray& ray, float& thit, LocalGeo& local){
	float t, t1, t2;
	Point p;
	Vector n;
	
	// Define commonly used vectors 
	Vector d = ray.dir;
	Vector e_c = ray.pos - center;
	float discriminant = sqr(d.dot_product(e_c)) - (d.dot_product(d) * (e_c.dot_product(e_c) - sqr(radius)));
	
	// Check discriminant values before evaluating for t
	if (discriminant < 0) {
		return false;
	} else if (discriminant == 0) {
		t = (d * -1).dot_product(e_c) / (d.dot_product(d)); 
	} else {
		t1 = ((d * -1).dot_product(e_c) + sqrt(discriminant)) / (d.dot_product(d));
		t2 = ((d * -1).dot_product(e_c) - sqrt(discriminant)) / (d.dot_product(d));
		if (t1 < t2) {
			t = t1;
		} else {
			t = t2;
		}
	}
	// If t is outside of the bounds, return false, else solve for the point and normal of the local geometry
	if (t < ray.tmin || t > ray.tmax) {
		return false;
	} else {
		p = ray.pos + (ray.dir * t);
		n = (p - center) / radius;
		thit = t;
		local.pos = p;
		local.norm = n.normalize();
		return true;
	}
}

bool Sphere::intersectP(Ray& ray){
  LocalGeo local;
  float thit;
  return Sphere::intersect(ray, thit, local);
};