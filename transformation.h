#ifndef __TRANSF_H_INCLUDED__   // if x.h hasn't been included yet...
#define __TRANSF_H_INCLUDED__

#include "cartesian.h"
#include "localgeo.h"
#include "matrix.h"

class Transformation {
	public:
		Matrix m, minvt;
		Transformation(Matrix mat, Matrix matinvt) {
			m = mat;
			minvt = matinvt;
		}
		Transformation() {
			m = *(new Matrix(0,0,0,0));
			minvt = *(new Matrix(0,0,0,0));
		}
		Point operator*(const Point&);
		Vector operator*(const Vector&);
		Normal operator*(const Normal&);
		Ray operator*(const Ray&);
		LocalGeo operator*(const LocalGeo&);
		Transformation operator*(Matrix&);
};

#endif