#include <stdio.h>
#include <iostream>
#include "transformation.h"

using namespace std;

Point Transformation::operator*(const Point& point) {
	Point* p = new Point();
	//cout << "check 1" << endl;
	p->x = (m.entries[0][0]*point.x) + (m.entries[0][1]*point.y) + (m.entries[0][2]*point.z) + (m.entries[0][3]*1);
	//cout << "check 2" << endl;
	p->y = (m.entries[1][0]*point.x) + (m.entries[1][1]*point.y) + (m.entries[1][2]*point.z) + (m.entries[1][3]*1);
	//cout << "check 3" << endl;
	p->z = (m.entries[2][0]*point.x) + (m.entries[2][1]*point.y) + (m.entries[2][2]*point.z) + (m.entries[2][3]*1);
	//cout << "check 4" << endl;
	return *p;
}

Vector Transformation::operator*(const Vector& vec) {
	Vector* v = new Vector();
	v->x = (m.entries[0][0]*vec.x) + (m.entries[0][1]*vec.y) + (m.entries[0][2]*vec.z);
	v->y = (m.entries[1][0]*vec.x) + (m.entries[1][1]*vec.y) + (m.entries[1][2]*vec.z);
	v->z = (m.entries[2][0]*vec.x) + (m.entries[2][1]*vec.y) + (m.entries[2][2]*vec.z);
	return *v;
}

Normal Transformation::operator*(const Normal& norm) {
	Vector* n = new Vector();
	n->x = (minvt.entries[0][0]*norm.x) + (minvt.entries[0][1]*norm.y) + (minvt.entries[0][2]*norm.z);
	n->y = (minvt.entries[1][0]*norm.x) + (minvt.entries[1][1]*norm.y) + (minvt.entries[1][2]*norm.z);
	n->z = (minvt.entries[2][0]*norm.x) + (minvt.entries[2][1]*norm.y) + (minvt.entries[2][2]*norm.z);
	return (*n).normalize();
}

Ray Transformation::operator*(const Ray& ray) {
	Ray* r = new Ray();
	r->pos = *this * ray.pos;
	r->dir = *this * ray.dir;
	r->tmin = ray.tmin;
	r->tmax = ray.tmax;
	return *r;
}

LocalGeo Transformation::operator*(const LocalGeo& lg) {
	//cout << "Transformation::operator* " << endl;
	LocalGeo* local = new LocalGeo();
	//cout << "New LocalGeo* declared" << endl;

	Point* p = new Point();
	//cout << "check 1" << endl;
	p->x = (m.entries[0][0]*lg.pos.x) + (m.entries[0][1]*lg.pos.y) + (m.entries[0][2]*lg.pos.z) + (m.entries[0][3]*1);
	//cout << "check 2" << endl;
	p->y = (m.entries[1][0]*lg.pos.x) + (m.entries[1][1]*lg.pos.y) + (m.entries[1][2]*lg.pos.z) + (m.entries[1][3]*1);
	//cout << "check 3" << endl;
	p->z = (m.entries[2][0]*lg.pos.x) + (m.entries[2][1]*lg.pos.y) + (m.entries[2][2]*lg.pos.z) + (m.entries[2][3]*1);
	//cout << "check 4" << endl;
	local->pos = *p;
	//cout << "local->pos = *this * lg.pos" << endl;

	Vector* n = new Vector();
	n->x = (minvt.entries[0][0]*lg.norm.x) + (minvt.entries[0][1]*lg.norm.y) + (minvt.entries[0][2]*lg.norm.z);
	n->y = (minvt.entries[1][0]*lg.norm.x) + (minvt.entries[1][1]*lg.norm.y) + (minvt.entries[1][2]*lg.norm.z);
	n->z = (minvt.entries[2][0]*lg.norm.x) + (minvt.entries[2][1]*lg.norm.y) + (minvt.entries[2][2]*lg.norm.z);
	local->norm = (*n).normalize();
	
	//cout << "Transformation::operator* about to return" << endl;
	return *local;
}

Transformation Transformation::operator*(Matrix& matrix) {
	Matrix m_new = m * matrix;
	Matrix minvt_new = (matrix.inverse() * m.inverse()).transpose(); 
	Transformation* t = new Transformation(m_new, minvt_new);
	return *t;
}