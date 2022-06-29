#pragma once
#include "CLine.h"
#include <vector>
#include "CVector.h"
#include "CTransform3.h"

using namespace std;

class TopLineShape
{
public:
	void ReadLine();
	void Translate(double tx, double ty, double tz);
	void Scale(double sx, double sy, double sz);
	void RotateX(double angle);
	void RotateY(double angle);
	void RotateZ(double angle);
	void SetCameraMatiax(
		double r11, double r12, double r13, double tx,
		double r21, double r22, double r23, double ty,
		double r31, double r32, double r33, double tz);
public:
	vector<CLine> OtmopLine; //斜二测投影轮廓
	vector<SurfaceUnit> Mesh; //三角形面片
	vector<CP3> P;
};

