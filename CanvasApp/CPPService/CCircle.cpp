#include "CCircle.h"

CCircle::CCircle()
{
	IsReverse = false;
	X0 = 0, Y0 = 0, Z0 = 0;
	Radius = 1;
	CP3 start(1, 0, 0);
	double angle = PI * 2 / 8;
	double angleNow = angle;
	for (int i = 0; i < 8; i++)
	{
		P.push_back(CP3(start.X + Radius * cos(angleNow), start.Y + Radius * sin(angleNow), Z0));
		angleNow += angle;
	}
	ReadMesh();
}

CCircle::CCircle(CP3 pos, double radius, double precision, bool isReverse)
{
	IsReverse = isReverse;
	X0 = pos.X, Y0 = pos.Y, Z0 = pos.Z;
	Radius = radius;
	CP3 start(X0, 0, Z0);
	double angle = PI * 2 / precision;
	double angleNow = angle;
	for (int i = 0; i < precision; i++)
	{
		P.push_back(CP3(start.X + Radius * cos(angleNow), start.Y + Radius * sin(angleNow), Z0));
		angleNow += angle;
	}
	ReadMesh();
}

CCircle::~CCircle()
{
}

void CCircle::ReadMesh()
{
	CP3 pos(X0, Y0, Z0);
	if (!IsReverse)
	{
		for (int i = 0; i < P.size() - 1; i++)
		{
			Mesh.push_back(SurfaceUnit(pos, P[i], P[i + 1]));
		}
		Mesh.push_back(SurfaceUnit(pos, P[P.size() - 1], P[0]));
	}
	else
	{
		for (int i = 0; i < P.size() - 1; i++)
		{
			Mesh.push_back(SurfaceUnit(P[i + 1], P[i], pos));
		}
		Mesh.push_back(SurfaceUnit(P[0], P[P.size() - 1], pos));
	}
}
