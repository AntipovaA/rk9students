#pragma once
#include<vector>
#include "PointWithDensity.h"

using namespace std;

namespace rk9 {

	struct RectLattice {

		//координаты вершин ограничивающего параллелепипеда, размеры в мм

		double
			Xmin = -100, 
			Xmax = +100,
			Ymin = -100,
			Ymax = +100,
			Zmin = -100,
			Zmax = +100;

		//создание прямоугольной решетки, pace - шаг решетки
		//возвращает вектор точек, лежащих в узлах решетки
		vector<PointWithDensity> GenerateRectLattice(double pace);
	};
}

