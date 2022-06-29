#pragma once
#include "CP3.h"
#include "CFace.h"
#include "TopLineShape.h"
#include "CTransform3.h"

class CPyramid :public TopLineShape
{
public:
	CPyramid();
	CPyramid(double width, double height);
	~CPyramid();
	void ReadPoint();
	void ReadMesh();
public:
	double Width;
	double Height;
};

