#include "CPAxis.h"

CPAxis::CPAxis()
{
	CAxis axis;
	XAxis = gcnew CPLine(axis.XAxis.StartPt.X, axis.XAxis.StartPt.Y, axis.XAxis.EndPt.X, axis.XAxis.EndPt.Y);
	YAxis = gcnew CPLine(axis.YAxis.StartPt.X, axis.YAxis.StartPt.Y, axis.YAxis.EndPt.X, axis.YAxis.EndPt.Y);
	ZAxis = gcnew CPLine(axis.ZAxis.StartPt.X, axis.ZAxis.StartPt.Y, axis.ZAxis.EndPt.X, axis.ZAxis.EndPt.Y);
	Pts = gcnew List<Point3D>();
	for (int i = 0; i < axis.P.size(); i++)
	{
		Pts->Add(Point3D(axis.P[i].X, axis.P[i].Y,axis.P[i].Z));
	}

}

CPAxis::~CPAxis()
{

}

void CPAxis::SetCameraMatiax(double r11, double r12, double r13, double tx, double r21, double r22, double r23, double ty, double r31, double r32, double r33, double tz)
{
	vector<CP3> pts;
	CAxis axis;
	for (int i = 0; i < Pts->Count; i++)
	{
		pts.push_back(CP3(Pts[i].X, Pts[i].Y, Pts[i].Z));
	}
	axis.P = pts;
	axis.SetCameraMatiax(r11, r12, r13, tx, r21, r22, r23, ty, r31, r32, r33, tz);
	XAxis = gcnew CPLine(axis.XAxis.StartPt.X, axis.XAxis.StartPt.Y, axis.XAxis.EndPt.X, axis.XAxis.EndPt.Y);
	YAxis = gcnew CPLine(axis.YAxis.StartPt.X, axis.YAxis.StartPt.Y, axis.YAxis.EndPt.X, axis.YAxis.EndPt.Y);
	ZAxis = gcnew CPLine(axis.ZAxis.StartPt.X, axis.ZAxis.StartPt.Y, axis.ZAxis.EndPt.X, axis.ZAxis.EndPt.Y);
	Pts = gcnew List<Point3D>();
	for (int i = 0; i < axis.P.size(); i++)
	{
		Pts->Add(Point3D(axis.P[i].X, axis.P[i].Y, axis.P[i].Z));
	}
}
