#pragma once
#include "TopLineShape.h"
#include "CLine.h"
class CAxis:public TopLineShape
{
public:
	CAxis();
	~CAxis();
	void SetCameraMatiax(double r11, double r12, double r13, double tx, double r21, double r22, double r23, double ty, double r31, double r32, double r33, double tz);
public:
	CLine XAxis, YAxis, ZAxis;
};

