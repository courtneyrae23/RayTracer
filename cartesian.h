#ifndef __CARTESIAN_H_INCLUDED__   // if x.h hasn't been included yet...
#define __CARTESIAN_H_INCLUDED__   //   #define this so the compiler knows it has been included


#include <math.h>

class Vector;

class Normal {
  public:
    float dot_product(Normal);
    float x, y, z;
    Normal(float a = 0.0, float b = 0.0, float c = 0.0) {
        float length = sqrt(a*a + b*b + c*c);
        if (length == 0.0) {
            x = 0.0;
            y = 0.0;
            z = 0.0;  
        } else {
            x = a / length;
            y = b / length;
            z = c / length;
        }
    };
    Normal operator+(const Normal&);
    Vector operator+(const Vector&);
    Normal operator-(const Normal&);
    Vector operator-(const Vector&);
    Vector operator*(float);
    Vector operator/(float);
    void print();
};

class Vector {
  public:
    float x, y, z;
    Vector(float a = 0.0, float b = 0.0, float c = 0.0) {
        x = a;
        y = b;
        z = c;
    };
    float dot_product(Vector);
    float dot_product(Normal);
    Vector cross_product(Vector);
    Vector operator+(const Vector&);
    Vector operator-(const Vector&);
    Vector operator-(const Normal&);
    Vector operator*(float);
    Vector operator/(float);
    void print();
    Normal normalize();
    float length();
};

class Point {
  public:
    float x, y, z;
    Point(float a = 0.0, float b = 0.0, float c = 0.0) {
        x = a;
        y = b;
        z = c;
    };
    Point operator+(const Vector&);
    Point operator*(const float);
    Point operator-(const Vector&);
    Vector operator-(const Point&);
    void print();
};

class Ray {
  public:
    Point pos;
    Vector dir;
    float tmin, tmax;
    Ray() {
        pos = *(new Point(0.0, 0.0, 0.0));
        dir = *(new Vector(0.0, 0.0, 0.0));
        tmin = 0.0;
        tmax = 0.0;
    }
};

#endif