#include <fstream>

#include "common/PolyModel.h"

using namespace std;

namespace rk9
{
	int PolyModel::ReadFromSTLFile(char * filename) {

		ifstream fin(filename, ios_base::binary);
		if (!fin) {
			return 1;
		}
		
		// ��������, ��� ���� ��������
		char buf[6];
		buf[5] = '\0';
		fin.read(buf, 5);
		if (string(buf) == "solid") {
			return 1;
		}

		// ���������� ��������� ������ 80 ����
		fin.seekg(80, fin.beg);

		unsigned triangles_count;
		fin.read( reinterpret_cast<char *>(&triangles_count), sizeof(unsigned));

		float coordinates[9];

		// ������� ������� ����� ��� ����� � ������������
		Points.reserve(3 * triangles_count);
		Triangles.reserve(triangles_count);

		for (unsigned i = 0; i < triangles_count; ++i) {
			// ���������� ������� (3 x 4 ����, float)
			fin.seekg(3 * sizeof (float), fin.cur);
			
			// ��������� ���������� ���� ������ ������������ (�� 3 ���������� �� �������)
			fin.read(reinterpret_cast<char *>(coordinates), 9 * sizeof(float));

			// ���������� 16 ��� "Attribute Byte Count"
			fin.seekg(sizeof(unsigned short), fin.cur);

			Point pt1, pt2, pt3;
			pt1.X = coordinates[0];
			pt1.Y = coordinates[1];
			pt1.Z = coordinates[2];

			pt2.X = coordinates[3];
			pt2.Y = coordinates[4];
			pt2.Z = coordinates[5];

			pt3.X = coordinates[6];
			pt3.Y = coordinates[7];
			pt3.Z = coordinates[8];

			Points.push_back(pt1);
			Points.push_back(pt2);
			Points.push_back(pt3);
			
			Triangle tr;
			tr.V[0] = i * 3;
			tr.V[1] = i * 3 + 1;
			tr.V[2] = i * 3 + 2;

			Triangles.push_back(tr);
		}

		return 0;
	}

	int PolyModel::WriteToSTLFile(char * filename) {
		
		ofstream fout(filename, ios_base::binary);
		if (!fout) {
			return 1;
		}

		// ������� ��������� 80 ����
		char header[80];
		fout.write(header, 80);

		// ������� ���-�� �������������
		unsigned triangles_count = Triangles.size();
		fout.write(reinterpret_cast<char *>(&triangles_count), sizeof(unsigned));

		// ������ �������������
		for (unsigned i = 0; i < triangles_count; ++i) {

			// ������� "�������" 3 � 4 ����
			float normal[3] = { 0.0, 0.0, 0.0 };
			fout.write(reinterpret_cast<char *>(normal), 12);

			// ������� ���������� ������������
			float coordinates[9];
			Point pt1, pt2, pt3;
			Triangle tr;

			tr = Triangles[i];
			pt1 = Points[tr.V[0]];
			pt2 = Points[tr.V[1]];
			pt3 = Points[tr.V[2]];

			coordinates[0] = static_cast<float>(pt1.X);
			coordinates[1] = static_cast<float>(pt1.Y);
			coordinates[2] = static_cast<float>(pt1.Z);
						   	 
			coordinates[3] = static_cast<float>(pt2.X);
			coordinates[4] = static_cast<float>(pt2.Y);
			coordinates[5] = static_cast<float>(pt2.Z);
						   	 
			coordinates[6] = static_cast<float>(pt3.X);
			coordinates[7] = static_cast<float>(pt3.Y);
			coordinates[8] = static_cast<float>(pt3.Z);

			fout.write(reinterpret_cast<char *>(coordinates), 9 * sizeof(float));

			// ������� "Attribute byte count" (16 ���)
			unsigned short attr_byte_count;
			fout.write(reinterpret_cast<char *>(&attr_byte_count), sizeof(unsigned short));

		}

		return 0;
	}

	void PolyModel::AddTriangle(Point p1, Point p2, Point p3)
	{
		int max_point_index = Points.size() - 1;

		Points.push_back(p1);
		Points.push_back(p2);
		Points.push_back(p3);

		Triangle tr;
		tr.V[0] = max_point_index + 1;
		tr.V[1] = max_point_index + 2;
		tr.V[2] = max_point_index + 3;

		Triangles.push_back(tr);
	}

	//return the number of triangles in polymodel
	unsigned PolyModel::GetTrianglesCount() {

		return Triangles.size();
	}

	//return the massive with 3 points of needed triangle, j is the index of triangle
	vector<Point>* PolyModel::GetTriangleVertices(unsigned j) {

		if (j > Points.size() * 3)
			return 0;

		vector<Point> *points = new vector<Point>;

		points->push_back(Points[j * 3]);
		points->push_back(Points[j * 3+1]);
		points->push_back(Points[j * 3+2]);
		
		return points;
	}
	
}