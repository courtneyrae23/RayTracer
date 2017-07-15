#include "camera.h"
#include <float.h>
#include <iostream>

using namespace std;

void Camera::generateRay(Sample& sample, Ray* ray) {
    Point* p = new Point();
    float u = (sample.x+0.5) / dimx;
    float v = (sample.y+0.5) / dimy;
    /*cout << "Camera::generateRay: " << endl;
    cout << u << " " << v << endl;
    cout << "Corner points: " << endl;
    cout << UL.x << " " << UL.y;
    cout << UR.x << " " << UR.y;
    cout << LL.x << " " << LL.y;
    cout << LR.x << " " << LR.y;*/
    p->x = UL.x + (UR.x - UL.x)*u;
    p->y = LL.y + (UL.y - LL.y)*v;
    p->z = LL.z;
    //p->print();
    ray->pos = eye;
    ray->dir = *p - eye;
    //ray->pos.print();
    //ray->dir.print();
    ray->tmin = 0;
    ray->tmax = FLT_MAX;

}