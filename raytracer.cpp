#include "raytracer.h"
#include <vector>
#include <float.h>
#include <math.h>

void RayTracer::trace(Ray& ray, int depth, Color& color) {
	if (depth > 5) {
        color.r = 0.0;
        color.g = 0.0;
        color.b = 0.0;
        return;
    }
    float thit;
    Intersection in = *(new Intersection(*(new LocalGeo()), new GeometricPrimitive()));
    if (!primitives->intersect(ray, thit, in)) {
        // No intersection
        //if (depth > 1) {
        //    cout << "no hit" << endl;
        //}
        color.r = 0.0;
        color.g = 0.0;
        color.b = 0.0;
        return;
    }
    //if (depth > 1) {
    //    cout << "HIT" << endl;
    //}
    //cout << "hit!" << endl;
    BRDF* brdf = new BRDF();
    //cout << "c1" << endl;
    // Obtain the brdf at intersection point
    //cout << in.primitive->mat << endl;
    //cout << "in.local.pos: ";
    //in.local.pos.print();
    in.primitive->mat->getBRDF(in.local, *brdf);
    //cout << "c2" << endl;
    // There is an intersection, loop through all light source
    std::vector<Light*>::iterator iter;
    //cout << "c3" << endl;
    int i = 0;
    Ray* lray = new Ray();
    //cout << "c4" << endl;
    Color* lcolor = new Color();
    //out << "double hit!" << endl;
    for (iter = lights.begin(); iter != lights.end(); iter++) {
        if (lights[i]->ambient) {
            color = color + (brdf->ka * lights[i]->color); 
        } else {
         	lights[i]->generateLightRay(in.local, *lray, *lcolor);
            // if(lray->dir.x < 0){
            //     cout << "IT'S WORKING" << endl;
            // }
//            cout << "Non ambient light" << endl;
//            lcolor->print();
    		// Check if the light is blocked or not
        	if (!primitives->intersectP(*lray)) {
//                cout << "Not occluded" << endl;
			// If not, do shading calculation for this light source
             	color = color + shading(in.local, *brdf, *lray, *lcolor, ray);
			} else {
                //cout << "Occluded" << endl;
                // lray->pos.print();
                // lray->dir.print();
                //if (depth > 1) {
                //    cout << "occluded" << endl;
                //}
			 	color = color + ((brdf->ka)*(*lcolor));
			}
		}
        i++;
	} 
	// Handle mirror reflection
	if (brdf->kr.r > 0 || brdf->kr.g > 0 || brdf->kr.b > 0) {
        //cout << "reflecting " << endl;
        Ray reflect = createReflectRay(in.local, ray);
        //reflect.dir.print();
        Color* tempColor = new Color();
        // Make a recursive call to trace the reflected ray
        trace(reflect, depth+1, *tempColor);
        //cout << "tempColor: ";
        //tempColor->print();
        color = color + (brdf->kr * (*tempColor));
    }
}

Color RayTracer::shading(LocalGeo local, BRDF brdf, Ray lray, Color lcolor, Ray ray) {
    //cout << "shading call" << endl;
	Color ambient = brdf.ka * lcolor;
	Color diffuse = brdf.kd * lcolor * max((float) 0.0, local.norm.dot_product(lray.dir.normalize()));
    //cout << "diffuse component: " << endl;
    //diffuse.print();
	Vector r_vec = (lray.dir*-1).normalize() + local.norm * (2 * (local.norm.dot_product(lray.dir.normalize())));
    Normal r = r_vec.normalize();
    //cout << "brdf.ks: ";
    //brdf.ks.print();
    //cout << "lcolor: ";
    //lcolor.print();
    //cout << "ray.dir*-1: ";
    //(ray.dir*-1).print();
    //cout << "r: ";
    //r.print();
	Color spec = brdf.ks * lcolor * pow(max((float) 0.0, (ray.dir*-1).normalize().dot_product(r)), brdf.sp);
    //cout << "specular: ";
    //spec.print();
    return  (ambient + diffuse + spec);
}

Ray RayTracer::createReflectRay(LocalGeo local, Ray ray) {
	Ray reflect = *(new Ray());
    reflect.dir = ray.dir.normalize() - (local.norm * (2 * (ray.dir.normalize().dot_product(local.norm))));
    //reflect.dir.print();
    reflect.pos = local.pos;
	reflect.tmin = 0.001;
	reflect.tmax = FLT_MAX;
    return reflect;
}