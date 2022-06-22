#pragma once
#include "CP3.h"
#include "CFace.h"
#include "TopLineShape.h"
#include "CTransform3.h"

class CPyramid :public TopLineShape
{
public:
	CPyramid();
	CPyramid(double edgeNum, double height);
	~CPyramid();
	void ReadPoint();
	void ReadLine();
	void ReadFace();

	void Translate(double tx, double ty, double tz);
	void Scale(double sx, double sy, double sz);
	void RotateX(double angle);
	void RotateY(double angle);
	void RotateZ(double angle);
public:
	double EdgeNum;
	double Height;
};

