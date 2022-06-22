#include "TopLineShape.h"

void TopLineShape::ReadLine()
{
	OtmopLine.clear();
	CTransform3 trans = CTransform3(Mesh);
	vector<CP2> pts = trans.ObliqueBinary();
	for (int i = 0; i < pts.size(); i += 3)
	{
		OtmopLine.push_back(CLine(pts[i], pts[i + 1]));
		OtmopLine.push_back(CLine(pts[i + 1], pts[i + 2]));
		OtmopLine.push_back(CLine(pts[i + 2], pts[i]));
	}
}


void TopLineShape::Translate(double tx, double ty, double tz)
{
	CTransform3 trans = CTransform3(Mesh);
	trans.Translate(tx, ty, tz);
	Mesh = trans.Mesh;
	ReadLine();
}

void TopLineShape::Scale(double sx, double sy, double sz)
{
	CTransform3 trans = CTransform3(Mesh);
	trans.Scale(sx, sy, sz);
	Mesh = trans.Mesh;
	ReadLine();
}

void TopLineShape::RotateX(double angle)
{
	CTransform3 trans = CTransform3(Mesh);
	trans.RotateX(angle);
	Mesh = trans.Mesh;
	ReadLine();
}

void TopLineShape::RotateY(double angle)
{
	CTransform3 trans = CTransform3(Mesh);
	trans.RotateY(angle);
	Mesh = trans.Mesh;
	ReadLine();
}

void TopLineShape::RotateZ(double angle)
{
	CTransform3 trans = CTransform3(Mesh);
	trans.RotateZ(angle);
	Mesh = trans.Mesh;
	ReadLine();
}