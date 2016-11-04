#include <iostream>
#include <conio.h>
#include <vector>

#include "RectLattice.h"
#include "PointWithDensity.h"
#include "fparser.h"

using namespace std;
using namespace rk9;

// ������� ��������� - ��
int main(int argc, char ** argv) {

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


//	std::cout << parser.Eval(values); // ����� ��������� �������� �������, ��������� �������� x, y � z
	_getch();

	return 0;
}
