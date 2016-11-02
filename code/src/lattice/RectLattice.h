#pragma once
#include<vector>
#include "PointWithDensity.h"

using namespace std;

namespace rk9 {

	struct RectLattice {

		//���������� ������ ��������������� ���������������, ������� � ��

		double
			Xmin = -100, 
			Xmax = +100,
			Ymin = -100,
			Ymax = +100,
			Zmin = -100,
			Zmax = +100;

		//�������� ������������� �������, pace - ��� �������
		//���������� ������ �����, ������� � ����� �������
		vector<PointWithDensity> GenerateRectLattice(double pace);
	};
}

