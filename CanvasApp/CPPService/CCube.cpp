#include "CCube.h"

CCube::CCube()
{
	P.resize(8);
	OtmopLine.resize(12);
	Width = 1, Length = 1, Height = 1;
	ReadPoint();
	ReadMesh();
	ReadLine();
}

CCube::CCube(CP3 position, double length, double width, double height)
{
	P.resize(8);
	OtmopLine.resize(12);
	Width = width, Length = length, Height = height;
	ReadPoint();
	ReadMesh();
	CTransform3 trans = CTransform3(Mesh);
	trans.Scale(length, width, height);
	trans.Translate(position.X, position.Y, position.Z);
	Mesh = trans.Mesh;
	ReadLine();
}

CCube::~CCube()
{

}

void CCube::ReadPoint()
{
	P[0].X = 0, P[0].Y = 0, P[0].Z = 0;
	P[1].X = 1, P[1].Y = 0, P[1].Z = 0;
	P[2].X = 1, P[2].Y = 1, P[2].Z = 0;
	P[3].X = 0, P[3].Y = 1, P[3].Z = 0;
	P[4].X = 0, P[4].Y = 0, P[4].Z = 1;
	P[5].X = 1, P[5].Y = 0, P[5].Z = 1;
	P[6].X = 1, P[6].Y = 1, P[6].Z = 1;
	P[7].X = 0, P[7].Y = 1, P[7].Z = 1;
}


void CCube::ReadMesh()
{
	Mesh.push_back(SurfaceUnit(P[2], P[1], P[0]));
	Mesh.push_back(SurfaceUnit(P[0], P[3], P[2]));
	Mesh.push_back(SurfaceUnit(P[2], P[3], P[7]));
	Mesh.push_back(SurfaceUnit(P[7], P[6], P[2]));
	Mesh.push_back(SurfaceUnit(P[6], P[7], P[4]));
	Mesh.push_back(SurfaceUnit(P[4], P[5], P[6]));
	Mesh.push_back(SurfaceUnit(P[5], P[4], P[0]));
	Mesh.push_back(SurfaceUnit(P[0], P[1], P[5]));
	Mesh.push_back(SurfaceUnit(P[5], P[1], P[2]));
	Mesh.push_back(SurfaceUnit(P[2], P[6], P[5]));
	Mesh.push_back(SurfaceUnit(P[3], P[0], P[4]));
	Mesh.push_back(SurfaceUnit(P[4], P[7], P[3]));
}




