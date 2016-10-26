#pragma once

#include "PolyModel.h"
#include "BoundingBox.h"

#include "common/common_api.h"

namespace rk9
{
	class COMMON_API Plane {
		double A, B, C, D;
	
	public:

		Plane() : 
			A(1.0), 
			B(0.0), 
			C(0.0), 
			D(0.0) {}

		Plane(double a, double b, double c, double d) :
			A(a),
			B(b),
			C(c),
			D(d) {}

		// Получить представление плоскости в виде многоугольника,
		// ограниченного данным Bounding Box'ом
		PolyModel GetPolyRepresentation(BoundingBox bbox);

		// Получить координаты точки пересечения плоскости с прямой.
		// point_1, point_2 - точки, через которые проходит заданная прямая;
		// result - искомая точка пересечения
		// Возвращает true, пересечение найдено. В противном случае возвращает false
		bool GetIntersectionWithLine(Point point_1, Point point_2, Point& result);


		// Получить координаты точки пересечения плоскости с отрезком.
		// point_1, point_2 - вершины отрезка;
		// result - искомая точка пересечения
		// Возвращает true, пересечение найдено. В противном случае возвращает false
		// Если точка пересечения есть, она обязательно принадлежит отрезку.
		bool GetIntersectionWithLineSegment(Point point_1, Point point_2, Point& result);
	};
}