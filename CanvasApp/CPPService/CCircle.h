#pragma once
#include "CP3.h"
#include "TopLineShape.h"
#include <vector>
#include <math.h>

#define PI acos(-1)

using namespace std;

class CCircle:public TopLineShape
{
public:
	CCircle();
	CCircle(CP3 pos, double radius, double precision = 8,bool isReverse=false);
	~CCircle();
	void ReadMesh();
public:
	double X0, Y0, Z0;
	double Radius;
private:
	bool IsReverse;
};

