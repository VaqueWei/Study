#include "CSphere.h"

CSphere::CSphere()
{
	Pos = CP3(0, 0, 0);
	Radius = 100;
	Precision = 8;
	double angleS = PI / Precision;
	double angleC = PI * 2 / Precision;
	double angS = PI * 3 / 2 + angleS;
	for (int i = 0; i < Precision / 2 - 1; i++)
	{
		CCircle circle(CP3(Pos.X, Pos.Y, sin(angS) * Radius), cos(angS) * Radius, Precision);
		Circles.push_back(circle);
		angS += angleS;
	}
	ReadPoint();
	ReadMesh();
	ReadLine();
}

CSphere::CSphere(CP3 pos, double radius, double precision)
{
	Pos = pos;
	Radius = radius;
	Precision = precision;
	double angleS = PI / Precision;
	double angleC = PI * 2 / Precision;
	double angS = PI * 3 / 2 + angleS;
	for (int i = 0; i < Precision; i++)
	{
		CCircle circle(CP3(Pos.X, Pos.Y, sin(angS) * Radius), cos(angS) * Radius, Precision);
		Circles.push_back(circle);
		angS += angleS;
	}
	ReadPoint();
	ReadMesh();
	ReadLine();
}

CSphere::~CSphere()
{
}

void CSphere::ReadMesh()
{
	CP3 ptBottom(Pos.X, Pos.Y, -Radius);
	CP3 ptTop(Pos.X, Pos.Y, Radius);
	for (int i = 0; i < Circles[0].P.size() - 1; i++)
	{
		Mesh.push_back(SurfaceUnit(ptBottom, Circles[0].P[i], Circles[0].P[(i + 1)]));
	}
	Mesh.push_back(SurfaceUnit(ptBottom, Circles[0].P[Circles[0].P.size() - 1], Circles[0].P[0]));
	vector<CP3> temp = Circles[Circles.size() - 1].P;
	for (int i = 0; i < temp.size() - 1; i++)
	{
		Mesh.push_back(SurfaceUnit(ptTop, temp[(i + 1)], temp[i]));
	}
	Mesh.push_back(SurfaceUnit(ptTop, temp[0], temp[temp.size() - 1]));

	for (int i = 0; i < Circles.size() - 1; i++)
	{
		vector<CP3> pts1 = Circles[i].P;
		vector<CP3> pts2 = Circles[(i + 1)].P;
		for (int j = 0; j < pts1.size() - 1; j++)
		{
			Mesh.push_back(SurfaceUnit(pts1[j], pts2[(j + 1)], pts1[(j + 1)]));
			Mesh.push_back(SurfaceUnit(pts1[j], pts2[j], pts2[(j + 1)]));
		}
		Mesh.push_back(SurfaceUnit(pts2[0], pts1[pts1.size() - 1], pts2[pts2.size() - 1]));
		Mesh.push_back(SurfaceUnit(pts1[pts1.size() - 1], pts2[pts2.size() - 1], pts2[0]));
	}
}

void CSphere::ReadPoint()
{
	CP3 ptBottom(Pos.X, Pos.Y, -Radius);
	CP3 ptTop(Pos.X, Pos.Y, Radius);
	P.push_back(ptBottom);
	for (int i = 0; i < Circles.size(); i++)
	{
		for (int j = 0; j < Circles[i].P.size(); j++)
		{
			P.push_back(Circles[i].P[j]);
		}
	}
	P.push_back(ptTop);
}
