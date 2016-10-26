#pragma once

#include <vector>

#include "Point.h"
#include "Triangle.h"

#include "common/common_api.h"
using namespace std;
namespace rk9
{
	class COMMON_API PolyModel {
	
		std::vector<Point> Points;
		std::vector<Triangle> Triangles;

	public:
		int ReadFromSTLFile(char * filename);
		int WriteToSTLFile(char * filename);

		void AddTriangle(Point p1, Point p2, Point p3);
		unsigned GetTrianglesCount();

		vector<Point>* GetTriangleVertices(unsigned index);
		


	};
}