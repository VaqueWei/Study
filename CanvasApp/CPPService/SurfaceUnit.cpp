#include "SurfaceUnit.h"

SurfaceUnit::SurfaceUnit()
{
	Pts.clear();
	Pts.push_back(CP3(0, 0, 0));
	Pts.push_back(CP3(1, 0, 0));
	Pts.push_back(CP3(0.5, 1, 0));
	GetVector();
}

SurfaceUnit::SurfaceUnit(CP3& pt1, CP3& pt2, CP3& pt3)
{
	
	Pts.clear();
	Pts.push_back(pt1);
	Pts.push_back(pt2);
	Pts.push_back(pt3);
	GetVector();
}

SurfaceUnit::~SurfaceUnit()
{
}

CVector SurfaceUnit::Normal()
{
	return V1.CrossProduct(V2).Normalize();
}

void SurfaceUnit::GetVector()
{
	V1 = CVector(Pts[0], Pts[1]);
	V2 = CVector(Pts[1], Pts[2]);
	V3 = CVector(Pts[2], Pts[0]);
}
