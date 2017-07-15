#include <iostream>
#include "primitive.h"
#include "shapes.h"
#include "localgeo.h"
#include "light.h"

using namespace std;

int main() {

    Material* material = new Material();

    Matrix* mat = new Matrix(0, 0, 0, 0);
    Transformation *trans = new Transformation(*mat, (*mat).inverse().transpose());

    Point* center = new Point(0.0, 0.0, 0.0);
    float r = 0.2;

    Sphere* s = new Sphere(*center, r);

    Point* a = new Point(1.0, 0.0, 0.0);
    Point * b = new Point(0.0, 1.0, 0.0);
    Point * c = new Point(0.0, 0.0, 1.0);

    Triangle* t = new Triangle(a, b, c);

    Point* e = new Point(1.0, 1.0, 1.0);
    Vector* d = new Vector(-1.0, -1.0, -1.0);

    GeometricPrimitive* sph = new GeometricPrimitive(*trans, *trans, s, material);
    GeometricPrimitive* tri = new GeometricPrimitive(*trans, *trans, t, material);
    std::vector<Primitive*> prims = {sph, tri};

    cout << prims[0] << endl;
    cout << prims[1] << endl;

    AggregatePrimitive* primitives = new AggregatePrimitive(prims);
    
    
    Ray* ray = new Ray();
    ray->pos = *e;
    ray->dir = *d;
    ray->tmin = 0;
    ray->tmax = 12;

    float thit;
    Intersection in;

    cout << primitives->intersect(*ray, thit, in) << endl;
    cout << thit << endl;

    BRDF brdf;
    in.local.pos.print();
    in.primitive->mat->getBRDF(in.local, brdf);
    //(*in).primitive->getBRDF((*in).local, brdf);
    brdf.ka.print();

    Point* lp = new Point(3.0, 3.0, 0.0);
    Color* lc = new Color(1.0, 1.0, 1.0);

    Light* l = new Light(*lp, *lc, 1, true, false, false);

    Ray lray;
    Color lcolor;

    l->generateLightRay(in.local, lray, lcolor);
    lcolor.print();
    lray.pos.print();
        // Check if the light is blocked or not
        // if (!primitives.intersectP(lray)) {
        //         // If not, do shading calculation for this light source
        //         *color += shading(in.local, brdf, lray, lcolor);
        //     } else {
        //         *color += brdf.ka * lcolor;
        //     }
        // }


    // Sampler* sampler = new Sampler(10, 10);
    // Sample* sample =  new Sample();

    // while (sampler->generateSample(sample)) {
    //     cout << sample->x << "," << sample->y << endl;
    // }
}