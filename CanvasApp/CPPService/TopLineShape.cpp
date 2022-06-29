#include "TopLineShape.h"

void TopLineShape::ReadLine()
{
	OtmopLine.clear();
	CTransform3 trans = CTransform3(Mesh);
	vector<CP2> pts = trans.ScreenSpace();
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

void TopLineShape::SetCameraMatiax(double r11, double r12, double r13, double tx, double r21, double r22, double r23, double ty, double r31, double r32, double r33, double tz)
{
	CTransform3 trans = CTransform3(Mesh);
	trans.SetCameraMatiax(r11, r12, r13, tx, r21, r22, r23, ty, r31, r32, r33, tz);
	Mesh = trans.Mesh;
	vector<CP2> pts = trans.ScreenSpace();
	for (int i = 0; i < pts.size(); i += 3)
	{
		OtmopLine.push_back(CLine(pts[i], pts[i + 1]));
		OtmopLine.push_back(CLine(pts[i + 1], pts[i + 2]));
		OtmopLine.push_back(CLine(pts[i + 2], pts[i]));
	}
}
