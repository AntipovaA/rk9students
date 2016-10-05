#pragma once
#include "PolyModel.h"
#include "BoundingBox.h"


namespace Modelling
{
	class Plane {
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

		// �������� ������������� ��������� � ���� ��������������,
		// ������������� ������ Bounding Box'��
		PolyModel GetPolyRepresentation(BoundingBox bbox);

		// �������� ���������� ����� ����������� ��������� � ������.
		// point_1, point_2 - �����, ����� ������� �������� �������� ������;
		// plane - ���������
		// result - ������� ����� �����������
		// ���������� true, ����������� �������. � ��������� ������ ���������� false
		bool GetIntersectionWithLine(Point point_1, Point point_2, Point& result);


		// �������� ���������� ����� ����������� ��������� � ��������.
		// point_1, point_2 - ������� �������;
		// plane - ���������
		// result - ������� ����� �����������
		// ���������� true, ����������� �������. � ��������� ������ ���������� false
		// ���� ����� ����������� ����, ��� ����������� ����������� �������.
		bool GetIntersectionWithLineSegment(Point point_1, Point point_2, Point& result);
	};
}