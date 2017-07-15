#include <vector>
#include <float.h>
#include "primitive.h"
#include <iostream>

bool GeometricPrimitive::intersect(Ray& ray, float& thit, Intersection& in) {
	Ray oray = worldToObj*ray;
    /*cout << "GeometricPrimitive::intersect: " << endl;
    ray.dir.print();
    ray.pos.print();
    oray.dir.print();
    oray.pos.print();*/
    LocalGeo olocal;                      
    if (!shape->intersect(oray, thit, olocal)) {
    	return false;
    }
    //cout << "thit: " << thit << endl;
    //cout << "olocal.pos: ";
    //olocal.pos.print();
    in.local = objToWorld*olocal;
    //cout << "in.local.pos.print(): ";
    //in.local.pos.print();
    in.primitive = this;

    //cout << "GeometricPrimitive::intersect about to return" << endl;
    return true;        
}

bool GeometricPrimitive::intersectP(Ray& ray) {
	//cout << "GeometricPrimitive::intersectP" << endl;
    Ray oray = worldToObj*ray;
    return shape->intersectP(oray);
}
void GeometricPrimitive::getBRDF(LocalGeo& local, BRDF& brdf) {
	mat->getBRDF(local, brdf);
}

bool AggregatePrimitive::intersect(Ray& ray, float& thit, Intersection& in) {
	std::vector<Primitive*>::iterator iter;
    int i = 0;
	float closest_t = FLT_MAX;
    float hit;
    bool intersect = false;
    Intersection inter = *(new Intersection(*(new LocalGeo()), new GeometricPrimitive()));
    
    for (iter = primitives.begin(); iter != primitives.end(); iter++) {
        //cout << primitives[i] << endl;
        if (primitives[i]->intersect(ray, hit, inter)) {
            intersect = true;
            if (hit < closest_t) {
                if(i == 0){
                //    cout << "closest_t: " << closest_t << endl;
                //    cout << "hit: " << hit << endl;
                }
                closest_t = hit;

            	thit = hit;
            	in = inter;
            }
        }
        i++;
    }

    return (closest_t != FLT_MAX && intersect);
}

bool AggregatePrimitive::intersectP(Ray& ray) {
	std::vector<Primitive*>::iterator iter;
	float closest_t = FLT_MAX;
    int i = 0;
    for (iter = primitives.begin(); iter != primitives.end(); iter++) {
        if (primitives[i]->intersectP(ray)) {
        	return true;
        }
        i++;
    }
    return false;
}

void AggregatePrimitive::getBRDF(LocalGeo& local, BRDF& brdf) {
	exit(1);
}
