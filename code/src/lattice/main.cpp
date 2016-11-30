/*пример заполнени€ строки аргументов
все размеры в миллиметрах
x-35 -30 30 -30 30 -30 30 0.3 0 10.0
argv[1] - не€вно заданна€ функци€, ограничивающа€ объем
argv[2] - argv[7] - координаты вершин ограничивающего параллелепипеда
argv[8] - шаг решетки при разбиении объема на точки
argv[9] - тип элементарной €чейки
argv[10] - размер элементарной €чейки
*/

#include <stdio.h>
#include <string>
#include "common/PolyModel.h"
#include "MarchingCubes.h"
#include "fparser.h"
#include "UnitCell.h"

using namespace rk9;
using namespace std;

double pi = 3.1415926535897932384626433832795;

struct PointFloat {
	float X, Y, Z;
};

bool run(MarchingCubes &mc, float isoval, string function, 
	double xmin, double xmax, double ymin, double ymax, double zmin, double zmax, double pace, int cell_type, double cell_size){
					
	enum Axis { X = 0, Y = 1, Z = 2 };

			// Parse formula
			FunctionParser fparser;								   
	fparser.Parse (function, "x,y,z,c,i");

	if (fparser.EvalError()) {
		printf("parse error\n");
		return false;
	}
	
	float rx = (xmax - xmin) / (mc.size().x - 1);
	float ry = (ymax - ymin) / (mc.size().y - 1);
	float rz = (zmax - zmin) / (mc.size().z - 1);

	glm::vec3 min_pos(xmin, ymin, zmin);
	glm::vec3 range(rx, ry, rz);

	//а - масштабный коэффициент
	double a = 2 * pi / cell_size;

	UnitCell * cell;
	switch (cell_type)
	{
	case 0: cell = new SchwarzPrimitive(a);
		break; 
	case 1: cell = new SchwarzPrimitivePinched(a);
		break; 
	case 2: cell = new SchoenGyroid(a);
		break;
	case 3: cell = new SchwarzW(a);
		break;
	case 4: cell = new NeoviusSurface(a);
		break;
	default: cell = new SchwarzPrimitive(a);
		break; 
	} 

	for (int i = 0; i < mc.size().x; i++) {
		float val[5];
		val[X] = (float)i * rx + xmin;
		for (int j = 0; j < mc.size().y; j++) {
			val[Y] = (float)j * ry + ymin;
			for (int k = 0; k < mc.size().z; k++) {
				val[Z] = (float)k * rz + zmin;

				auto w = fparser.Eval(val) - isoval;

				if (w > 0.0) {
					mc.set_data(w, glm::ivec3(i, j, k)); }
				if (w <= 0.0) {
					double build_cell = cell -> Eval(val[X],val[Y],val[Z]);
					mc.set_data(build_cell, glm::ivec3(i, j, k));
				}
			}
		}
	}

	// Run MC
	mc.SetAlgorithm(MarchingCubes::TopologicalMarchingCubes);
	mc.run();

	// Rescale positions
	for (int i = 0; i < mc.nverts(); ++i) {
		Vertex &v = mc.vertices()[i];
		v.pos = range * v.pos + min_pos;
		v.n = glm::normalize(v.n);
	}

	return true;
}

int main (int argc, char ** argv) {

	string function (argv[1]);

	double xmin = stod(argv[2]); 
	double xmax = stod(argv[3]); 
	double ymin = stod(argv[4]);
	double ymax = stod(argv[5]);
	double zmin = stod(argv[6]);
	double zmax = stod(argv[7]);

	double pace = stod(argv[8]);

	/*выбор типа решетки
	0 - Schwarz_Primitive;
	1 - Schwarz_Primitive_pinched
	2 - Schoen_Gyroid
	3 - Schwarz_W
	4 - Neovius_Surface
	ѕо умолчанию строитс€ Schwarz_Primitive
	*/
	int cell_type = stoi(argv[9]);
	double cell_size = stod(argv[10]);

	int cells_count = (int) ((xmax - xmin) / pace);

 	MarchingCubes mc(glm::ivec3(cells_count, cells_count, cells_count));
	mc.Setup();
	run(mc, 0, function, xmin, xmax, ymin, ymax, zmin, zmax, pace, cell_type, cell_size);

	vector<PointFloat> pts(mc.nverts());

	mc.FreeUnusedArrays();

	rk9::PolyModel m;

	for (int i = 0; i < mc.ntrigs(); ++i) {
		auto tri = mc.trig(i);

		rk9::Point p[3];

		for (int t = 0; t < 3; ++t) {
			auto vertex = mc.vert(tri.ids[t]).pos;
			p[t].X = vertex.x;
			p[t].Y = vertex.y;
			p[t].Z = vertex.z;
		}

		m.AddTriangle(p[0], p[1], p[2]);
	}

	string filename = string("output") + to_string(cell_type) + string(" cell_size") + to_string(cell_size) + string(".stl");

	m.WriteToSTLFile(filename.c_str());

	return 0;
}