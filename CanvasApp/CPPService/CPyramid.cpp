#include "CPyramid.h"

CPyramid::CPyramid()
{
	P.resize(4);
	Width = 1, Height = 1;
	ReadPoint();
	ReadMesh();
	ReadLine();
}

CPyramid::CPyramid(double width, double height)
{
	P.resize(4);
	Width = width, Height = height;
	ReadPoint();
	ReadMesh();
	CTransform3 trans = CTransform3(Mesh);
	trans.Scale(width, width*0.866, height);
	Mesh = trans.Mesh;
	ReadLine();
}

CPyramid::~CPyramid()
{
}

void CPyramid::ReadPoint()
{
	P[0].X = 0, P[0].Y = 0, P[0].Z = 0.866;
	P[1].X = 0, P[1].Y = 0.577, P[1].Z = 0;
	P[2].X = -0.5, P[2].Y = -0.289, P[2].Z = 0;
	P[3].X = 0.5, P[3].Y = -0.289, P[3].Z = 0;
}

void CPyramid::ReadMesh()
{
	Mesh.push_back(SurfaceUnit(P[1], P[2], P[3]));
	Mesh.push_back(SurfaceUnit(P[0], P[1], P[2]));
	Mesh.push_back(SurfaceUnit(P[0], P[2], P[3]));
	Mesh.push_back(SurfaceUnit(P[0], P[3], P[1]));
}


