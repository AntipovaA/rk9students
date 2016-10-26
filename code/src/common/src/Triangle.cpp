#include"common/Triangle.h"

using namespace std;

namespace rk9 {

//find parameters A,B,C,D of normal.
double* Triangle::GetNormal() {

	double *params = new double[4];

	//find coordinates of vectors of triangle's vertices
	double p12x = tr->at(1).X - tr->at(0).X;
	double p12y = tr->at(1).Y - tr->at(0).Y;
	double p12z = tr->at(1).Z - tr->at(0).Z;

	double p13x = tr->at(2).X - tr->at(0).X;
	double p13y = tr->at(2).Y - tr->at(0).Y;
	double p13z = tr->at(2).Z - tr->at(0).Z;

	params[0] = p12y*p13z - p13y*p12z;
	params[1] = -p12x*p13z + p13x*p12z;
	params[2] = p12x*p13y - p13x*p12z;
	params[3] = -params[0] * tr->at(1).X - params[1] * tr->at(1).Y - params[2] * tr->at(1).Z;

	return params;
}
}