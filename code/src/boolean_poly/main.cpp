#include <vector>
#include "common/PolyModel.h"
#include "common/Point.h"

using namespace std;
using namespace rk9;

// Поиск пересечения двух многогранников
// model_a, model_b - исходные параметры
// Возвращает координаты точек, образующих контур пересечения
vector<Point> GetIntersectionPoints(PolyModel model_a, PolyModel model_b);

void IntersectTriangles(vector<Point> *, vector<Point> *, vector<Point> *);
void IntersectEdgeTriangle(Point, Point, vector<Point> *, double *, vector<Point> *);
bool IsPointInsideTriangle(Point, vector<Point>*);
double TriangleArea(double, double, double);
bool IsPlaneBetweenTriangle(vector<Point> *, vector<Point> *);

const double EPSILON = 1E-10;

int main(int argc, char ** argv) {

	PolyModel model_a, model_b;

	vector<Point> intersection_points = GetIntersectionPoints(model_a, model_b);

	return 0;
}

vector<Point> GetIntersectionPoints(PolyModel model_a, PolyModel model_b) {

	vector<Point> points;

	unsigned triangles_count_A = model_a.GetTrianglesCount();
	unsigned triangles_count_B = model_b.GetTrianglesCount();

	for (unsigned i = 0; i < triangles_count_A; i++) {

		vector<Point> points_of_triangle_i = model_a.GetTriangleVertices(i);
		for (unsigned j = 0; j < triangles_count_B; j++) {

			vector<Point> points_of_triangle_j = model_b.GetTriangleVertices(j);

			//points of intersection of 2 triangles
			IntersectTriangles(points_of_triangle_i, points_of_triangle_j, points); 

		}
	}
	return points;
}

void IntersectTriangles(vector<Point> points_of_triangle_i, vector<Point> points_of_triangle_j, vector<Point> points) {

	if (IsPlaneBetweenTriangle(points_of_triangle_i, points_of_triangle_j) == false) {

		double *normal = GetTriangleNormal(points_of_triangle_j); //find parameters A,B,C,D of normal

		IntersectEdgeTriangle(points_of_triangle_i.at(0), points_of_triangle_i.at(1), points_of_triangle_j, normal, points);  //finding the intersection between the edge of 
		IntersectEdgeTriangle(points_of_triangle_i.at(0), points_of_triangle_i.at(2), points_of_triangle_j, normal, points);  //one triangle and plane of another
		IntersectEdgeTriangle(points_of_triangle_i.at(1), points_of_triangle_i.at(2), points_of_triangle_j, normal, points);

		normal = GetTriangleNormal(points_of_triangle_i);

		IntersectEdgeTriangle(points_of_triangle_j.at(0), points_of_triangle_j.at(1), points_of_triangle_i, normal, points);
		IntersectEdgeTriangle(points_of_triangle_j.at(0), points_of_triangle_j.at(2), points_of_triangle_i, normal, points);
		IntersectEdgeTriangle(points_of_triangle_j.at(1), points_of_triangle_j.at(2), points_of_triangle_i, normal, points);
	}

}

void IntersectEdgeTriangle(Point point1, Point point2, vector<Point> *points_of_triangle_j, double *normal, vector<Point> *points) {

	double p1 = point2.X - point1.X;
	double p2 = point2.Y - point1.Y;
	double p3 = point2.Z - point1.Z;
	if ((normal[0] * p1 + normal[1] * p2 + normal[2] * p3) != 0) {   //if A*p1+B*p2+C*p3=0 so line lies in plane or paralells it

		double t0 = (-normal[3] - normal[2] * point1.Z - normal[1] * point1.Y - normal[0] * point1.X) /
			(normal[0] * p1 + normal[1] * p2 + normal[2] * p3);

		double X0 = p1*t0 + point1.X;
		double Y0 = p2*t0 + point1.Y;
		double Z0 = p3*t0 + point1.Z;

		Point pp;
		pp.X = X0;
		pp.Y = Y0;
		pp.Z = Z0;

		if (IsPointInsideTriangle(pp, points_of_triangle_j)) // check if finded point lies in triangle 
		{
			points->push_back(pp);
		}

	}
}

bool IsPointInsideTriangle(Point pp, vector<Point> *tr) {

	double AB = sqrt(pow(tr->at(0).X - tr->at(1).X, 2) + pow(tr->at(0).Y - tr->at(1).Y, 2) + pow(tr->at(0).Z - tr->at(1).Z, 2));
	double BC = sqrt(pow(tr->at(1).X - tr->at(2).X, 2) + pow(tr->at(1).Y - tr->at(2).Y, 2) + pow(tr->at(1).Z - tr->at(2).Z, 2));
	double AC = sqrt(pow(tr->at(0).X - tr->at(2).X, 2) + pow(tr->at(0).Y - tr->at(2).Y, 2) + pow(tr->at(0).Z - tr->at(2).Z, 2));

	double AP = sqrt(pow(pp.X - tr->at(0).X, 2) + pow(pp.Y - tr->at(0).Y, 2) + pow(pp.Z - tr->at(0).Z, 2));
	double BP = sqrt(pow(pp.X - tr->at(1).X, 2) + pow(pp.Y - tr->at(1).Y, 2) + pow(pp.Z - tr->at(1).Z, 2));
	double CP = sqrt(pow(pp.X - tr->at(2).X, 2) + pow(pp.Y - tr->at(2).Y, 2) + pow(pp.Z - tr->at(2).Z, 2));

	double diff = TriangleArea(AP, BP, AB) + TriangleArea(AP, CP, AC) + TriangleArea(BP, CP, BC) - TriangleArea(AB, BC, AC);

	if (diff < EPSILON)
		return true;
	else return false;
}

double TriangleArea(double a, double b, double c) { //a,b,c - edges(length) of triangle
	double p = (a + b + c) / 2;
	return sqrt(p*(p - a)*(p - b)*(p - c));
}

//check if there may be plane between triangles(all points of tr1 are on the one side of points of tr2)
bool IsPlaneBetweenTriangle(vector<Point> *tr1, vector<Point> *tr2) {

	if ((tr1->at(0).X < tr2->at(0).X && tr1->at(0).Y < tr2->at(0).Y && tr1->at(0).Z < tr2->at(0).Z&&
		 tr1->at(0).X < tr2->at(1).X && tr1->at(0).Y < tr2->at(1).Y && tr1->at(0).Z < tr2->at(1).Z&&
		 tr1->at(0).X < tr2->at(2).X && tr1->at(0).Y < tr2->at(2).Y && tr1->at(0).Z < tr2->at(2).Z&&
		 tr1->at(1).X < tr2->at(0).X && tr1->at(1).Y < tr2->at(0).Y && tr1->at(1).Z < tr2->at(0).Z&&
		 tr1->at(1).X < tr2->at(1).X && tr1->at(1).Y < tr2->at(1).Y && tr1->at(1).Z < tr2->at(1).Z&&
		 tr1->at(1).X < tr2->at(2).X && tr1->at(1).Y < tr2->at(2).Y && tr1->at(1).Z < tr2->at(2).Z&&
		 tr1->at(2).X < tr2->at(0).X && tr1->at(2).Y < tr2->at(0).Y && tr1->at(2).Z < tr2->at(0).Z&&
		 tr1->at(2).X < tr2->at(1).X && tr1->at(2).Y < tr2->at(1).Y && tr1->at(2).Z < tr2->at(1).Z&&
		 tr1->at(2).X < tr2->at(2).X && tr1->at(2).Y < tr2->at(2).Y && tr1->at(2).Z < tr2->at(2).Z)
		 ||
		(tr1->at(0).X > tr2->at(0).X && tr1->at(0).Y > tr2->at(0).Y && tr1->at(0).Z > tr2->at(0).Z&&
		 tr1->at(0).X > tr2->at(1).X && tr1->at(0).Y > tr2->at(1).Y && tr1->at(0).Z > tr2->at(1).Z&&
		 tr1->at(0).X > tr2->at(2).X && tr1->at(0).Y > tr2->at(2).Y && tr1->at(0).Z > tr2->at(2).Z&&
		 tr1->at(1).X > tr2->at(0).X && tr1->at(1).Y > tr2->at(0).Y && tr1->at(1).Z > tr2->at(0).Z&&
		 tr1->at(1).X > tr2->at(1).X && tr1->at(1).Y > tr2->at(1).Y && tr1->at(1).Z > tr2->at(1).Z&&
		 tr1->at(1).X > tr2->at(2).X && tr1->at(1).Y > tr2->at(2).Y && tr1->at(1).Z > tr2->at(2).Z&&
		 tr1->at(2).X > tr2->at(0).X && tr1->at(2).Y > tr2->at(0).Y && tr1->at(2).Z > tr2->at(0).Z&&
		 tr1->at(2).X > tr2->at(1).X && tr1->at(2).Y > tr2->at(1).Y && tr1->at(2).Z > tr2->at(1).Z&&
		 tr1->at(2).X > tr2->at(2).X && tr1->at(2).Y > tr2->at(2).Y && tr1->at(2).Z > tr2->at(2).Z))

		return true;

}
