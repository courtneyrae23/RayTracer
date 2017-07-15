#include "cartesian.h"
#include <iostream>
using namespace std;

inline float sqr(float x) { return x*x; };

float Vector::dot_product(Vector vec) {
  return x * vec.x + y * vec.y + z * vec.z;
}

float Vector::dot_product(Normal norm) {
  return x * norm.x + y * norm.y + z * norm.z;
}

void Vector::print() {
  cout << "[" << x << "," << y << "," << z  << "]" << endl;
}

Vector Vector::cross_product(Vector vec) {
  Vector* v = new Vector();
  v->x = y*vec.z - z*vec.y;
  v->y = z*vec.x - x*vec.z;
  v->z = x*vec.y - y*vec.x;
  return *v;
}

Vector Vector::operator+(const Vector& vec) {
  Vector* v = new Vector();
  v->x = x + vec.x;
  v->y = y + vec.y;
  v->z = z + vec.z;
  return *v;
}
 
Vector Vector::operator-(const Vector& vec) {
  Vector* v = new Vector();
  v->x = x - vec.x;
  v->y = y - vec.y;
  v->z = z - vec.z;
  return *v;
} 

Vector Vector::operator-(const Normal& vec) {
  Vector* v = new Vector();
  v->x = x - vec.x;
  v->y = y - vec.y;
  v->z = z - vec.z;
  return *v;
} 

Vector Vector::operator*(float c) {
  Vector* v = new Vector();
  v->x = c * x;
  v->y = c * y;
  v->z = c * z;
  return *v;
}

Vector Vector::operator/(float c) {
  Vector* v = new Vector();
  v->x = x / c;
  v->y = y / c;
  v->z = z / c;
  return *v;
}

float Vector::length() {
  return sqrt(sqr(x) + sqr(y) + sqr(z));
}
 
Normal Vector::normalize() {
  Normal* n = new Normal();
  float length = sqrt(sqr(x) + sqr(y) + sqr(z));
  if (length == 0.0) {
    n->x = 0;
    n->y = 0;
    n->z = 0;  
  } else {
    n->x = x / length;
    n->y = y / length;
    n->z = z / length;
  }
  return *n;
}

Normal Normal::operator+(const Normal& norm) {
  Normal* n = new Normal();

  n->x = x + norm.x;
  n->y = y + norm.y;
  n->z = z + norm.z;

  float length = sqrt(sqr(n->x) + sqr(n->y) + sqr(n->z));
  if (length == 0.0) {
    n->x = 0;
    n->y = 0;
    n->z = 0;  
  } else {
    n->x = n->x / length;
    n->y = n->y / length;
    n->z = n->z / length;
  }
  return *n;
}

float Normal::dot_product(Normal norm) {
  return x * norm.x + y * norm.y + z * norm.z;
}

Normal Normal::operator-(const Normal& norm) {
  Normal* n = new Normal();

  n->x = x - norm.x;
  n->y = y - norm.y;
  n->z = z - norm.z;

  float length = sqrt(sqr(n->x) + sqr(n->y) + sqr(n->z));
  if (length == 0.0) {
    n->x = 0;
    n->y = 0;
    n->z = 0;  
  } else {
    n->x = n->x / length;
    n->y = n->y / length;
    n->z = n->z / length;
  }
  return *n;
}

Vector Normal::operator-(const Vector& norm) {
  Vector* n = new Vector();

  n->x = x - norm.x;
  n->y = y - norm.y;
  n->z = z - norm.z;

  return *n;
}

Vector Normal::operator+(const Vector& norm) {
  Vector* n = new Vector();

  n->x = x + norm.x;
  n->y = y + norm.y;
  n->z = z + norm.z;

  return *n;
}

Vector Normal::operator*(float c) {
  Vector* v = new Vector();
  v->x = c * x;
  v->y = c * y;
  v->z = c * z;
  return *v;
}

Vector Normal::operator/(float c) {
  Vector* v = new Vector();
  v->x = x / c;
  v->y = y / c;
  v->z = z / c;
  return *v;
}


void Normal::print() {
  cout << "[" << x << "," << y << "," << z  << "]" << endl;
}

Point Point::operator+(const Vector& vec) {
  Point* p = new Point();
  p->x = x + vec.x;
  p->y = y + vec.y;
  p->z = z + vec.z;
  return *p;
}

Point Point::operator-(const Vector& vec) {
  Point* p = new Point();
  p->x = x - vec.x;
  p->y = y - vec.y;
  p->z = z - vec.z;
  return *p;
}

Point Point::operator*(const float f) {
  Point* p = new Point();
  p->x = x * f;
  p->y = y * f;
  p->z = z * f;
  return *p;
}

Vector Point::operator-(const Point& point) {
  Vector* v = new Vector();
  v->x = x - point.x;
  v->y = y - point.y;
  v->z = z - point.z;
  return *v;
}

void Point::print() {
  cout << "[" << x << "," << y << "," << z  << "]" << endl;
}
