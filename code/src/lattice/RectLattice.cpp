#include "RectLattice.h"
#include "PointWithDensity.h"
#include <vector>

using namespace std;

namespace rk9 
{

vector <PointWithDensity> RectLattice::GenerateRectLattice(double pace) {

	vector <PointWithDensity> points;
	PointWithDensity point;

	for (double Z = Zmin; Z < Zmax ; Z += pace)
		for (double Y = Ymin; Y < Ymax; Y += pace)
 			for (double X = Xmin; X < Xmax; X += pace) {
				point.X = X;
				point.Y = Y;
				point.Z = Z;

				points.push_back(point);
			}
	 
		return points;
	}
}