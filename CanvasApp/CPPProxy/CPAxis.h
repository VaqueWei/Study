#pragma once
#include "TopCpLineShape.h"
#include "CPLine.h"
#include "CAxis.h"

public ref class CPAxis:public TopCpLineShape
{
public:
	CPAxis();
	~CPAxis();
	void SetCameraMatiax(
		double r11, double r12, double r13, double tx,
		double r21, double r22, double r23, double ty,
		double r31, double r32, double r33, double tz);
public:
	CPLine^ XAxis, ^YAxis, ^ZAxis;
	List<Point3D>^ Pts;
};

