#include <iostream>
#include <conio.h>
#include <vector>

#include "RectLattice.h"
#include "PointWithDensity.h"
#include "fparser.h"

using namespace std;
using namespace rk9;

// единицы изменения - мм
int main(int argc, char ** argv) {

	// Это приготовления, чтобы можно было вызывать функцию Eval
	FunctionParser parser; // Создать парсер - экземпляр класса FunctionParser

	string str(argv[1]);
	parser.Parse(str, "x,y,z"); // Передать ему на обработку вот эту формулу

	if (parser.EvalError()) // Нужно, чтобы проверить на опечатки и прочие ошибки, т.к. функция задается произвольной строкой
	{
		printf("parse error\n");
		return false;
	}

		RectLattice reclat;
	reclat.Xmin = stod (argv[2]); // считывание координат вершин параллелепипеда
	reclat.Xmax = stod (argv[3]); // stod - преобразование string to double
	reclat.Ymin = stod (argv[4]);
	reclat.Ymax = stod (argv[5]);
	reclat.Zmin = stod (argv[6]);
	reclat.Zmax = stod (argv[7]);

	double pace = stod(argv[8]); //шаг решетки

	vector <PointWithDensity> Points = reclat.GenerateRectLattice(pace);
	const float values[3]{ 2.0, 2.0, 2.0 };

	std::cout << parser.Eval(values); // Здесь вычисляем значение функции, передавая массивом x, y и z
	_getch();

	return 0;
}
