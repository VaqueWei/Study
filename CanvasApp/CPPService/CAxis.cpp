#include "CAxis.h"

CAxis::CAxis()
{
	P.push_back(CP3(0, 0, 0));
	P.push_back(CP3(100, 0, 0));
	P.push_back(CP3(0, 100, 0));
	P.push_back(CP3(0, 0, 100));
	CTransform3 trans(P);
	vector<CP2> pts = trans.ScreenSpaceAll();
	XAxis = CLine(pts[0], pts[1]);
	YAxis = CLine(pts[0], pts[2]);
	ZAxis = CLine(pts[0], pts[3]);
}

CAxis::~CAxis()
{
}

void CAxis::SetCameraMatiax(double r11, double r12, double r13, double tx, double r21, double r22, double r23, double ty, double r31, double r32, double r33, double tz)
{
	CTransform3 trans = CTransform3(P);
	trans.SetCameraMatiax(r11, r12, r13, tx, r21, r22, r23, ty, r31, r32, r33, tz);
	vector<CP2> pts = trans.ScreenSpaceAll();
	XAxis = CLine(pts[0], pts[1]);
	YAxis = CLine(pts[0], pts[2]);
	ZAxis = CLine(pts[0], pts[3]);
}