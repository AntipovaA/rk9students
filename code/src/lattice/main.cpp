#include <iostream>
#include <conio.h>
#include <vector>

#include "RectLattice.h"
#include "PointWithDensity.h"
#include "fparser.h"
#include "MarchingCubes.h"

using namespace std;
using namespace rk9;

// ������� ��������� - ��
int main(int argc, char ** argv) {

	float isoval = 0.0;

	int   originalMC = 0;

	MarchingCubes mc;
	
	mc.set_resolution(2, 2, 2);

	mc.init_all();

	int i, j, k;
	
	float rx = 4;
	float ry = 4;
	float rz = 4;
	
	for (i = 0; i < 2; i++)	{

		float x = (float)i * rx + (-2);

		for (j = 0; j < 2; j++)	{

			float y = (float)j * ry + (-2);

			for (k = 0; k < 2; k++) {
				float z = (float)k * rz + (-2);

				float w = x - isoval;
				mc.set_data(w, i, j, k);
			}
		}
	}
	
	mc.set_method(originalMC == 1);
	mc.run();

/*
	// ��� �������������, ����� ����� ���� �������� ������� Eval
//	FunctionParser parser; // ������� ������ - ��������� ������ FunctionParser

	string str(argv[1]);
//	parser.Parse(str, "x,y,z"); // �������� ��� �� ��������� ��� ��� �������

//	if (parser.EvalError()) // �����, ����� ��������� �� �������� � ������ ������, �.�. ������� �������� ������������ �������
//	{
//		printf("parse error\n");
//		return false;
//	}

		RectLattice reclat;
	reclat.Xmin = stod (argv[2]); // ���������� ��������� ������ ���������������
	reclat.Xmax = stod (argv[3]); // stod - �������������� string to double
	reclat.Ymin = stod (argv[4]);
	reclat.Ymax = stod (argv[5]);
	reclat.Zmin = stod (argv[6]);
	reclat.Zmax = stod (argv[7]);

	double pace = stod(argv[8]); //��� �������

vector <PointWithDensity> Nodes = reclat.GenerateRectLattice(pace);

vector <PointWithDensity> LatticeNodes = reclat.DefineNodeDensity(str, Nodes); 


//std::cout << CalculateFuncValue(str, p);


	//const float values[3]{ 2.0, 2.0, 2.0 };


//	std::cout << parser.Eval(values); // ����� ��������� �������� �������, ��������� �������� x, y � z */

	_getch();

	return 0;
}
