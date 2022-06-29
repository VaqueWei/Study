#include "CCylind.h"

CCylind::CCylind()
{
	Radius = 1, Height = 2;
	CCircle bottom(CP3(0, 0, 0), Radius, true);
	CCircle top(CP3(0, 0, Height), Radius);
	ReadPoint(bottom, top);
	ReadMesh(bottom, top);
	ReadLine();
}

CCylind::CCylind(CP3 pos, double radius, double height, double precision)
{
	if (precision < 4)
	{
		precision = 4;
	}
	Pos = pos;
	Radius = radius, Height = height;
	CCircle bottom(pos, Radius, precision, true);
	CCircle top(CP3(pos.X, pos.Y, pos.Z + Height), Radius, precision);
	ReadPoint(bottom, top);
	ReadMesh(bottom, top);
	ReadLine();
}

CCylind::~CCylind()
{
}

void CCylind::ReadPoint(CCircle bottom, CCircle top)
{
	for (int i = 0; i < bottom.P.size(); i++)
	{
		P.push_back(top.P[i]);
		P.push_back(bottom.P[i]);
	}
}

void CCylind::ReadMesh(CCircle& bottom, CCircle& top)
{
	int size = bottom.P.size();
	for (int i = 0; i < size - 1; i++)
	{
		Mesh.push_back(SurfaceUnit(bottom.P[i], bottom.P[i + 1], top.P[i]));
		Mesh.push_back(SurfaceUnit(top.P[i], bottom.P[i + 1], top.P[i + 1]));
	}
	//Mesh.push_back(SurfaceUnit(bottom.P[size - 2], bottom.P[size - 1], top.P[size - 2]));
	//Mesh.push_back(SurfaceUnit(top.P[size - 2], bottom.P[size - 1], top.P[size - 2]));
	Mesh.push_back(SurfaceUnit(bottom.P[size - 1], bottom.P[0], top.P[size - 1]));
	Mesh.push_back(SurfaceUnit(top.P[size - 1], bottom.P[0], top.P[0]));

	for (int i = 0; i < bottom.Mesh.size(); i++)
	{
		Mesh.push_back(bottom.Mesh[i]);
		Mesh.push_back(top.Mesh[i]);
	}
}
