#pragma once
#include "CCircle.h"
#include "TopLineShape.h"
#include "CCircle.h"

class CCylind :public TopLineShape
{
public:
	CCylind();
	CCylind(CP3 pos, double radius, double height, double precision = 8);
	~CCylind();
	void ReadPoint(CCircle c1, CCircle c2);
	void ReadMesh(CCircle& c1, CCircle& c2);
public:
	double Radius, Height;
	CP3 Pos;
};

