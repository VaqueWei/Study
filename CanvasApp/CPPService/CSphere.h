#pragma once
#include "TopLineShape.h"
#include <math.h>
#include "CCircle.h"

#define PI acos(-1)

class CSphere:public TopLineShape
{
public:
	CSphere();
	CSphere(CP3 pos, double radius, double precision = 16);
	~CSphere();
	void ReadMesh();
	void ReadPoint();
public:
	CP3 Pos;
	double Radius;
private:
	vector<CCircle> Circles;
	double Precision;
};

