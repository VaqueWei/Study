#pragma once
#include "CP3.h"
#include <vector>
#include "CVector.h"
using namespace std;

class SurfaceUnit
{
public:
	SurfaceUnit();
	SurfaceUnit(CP3& pt1, CP3& pt2, CP3& pt3);
	~SurfaceUnit();
	CVector Normal();
private:
	void GetVector();
public:
	vector<CP3> Pts;
	CVector V1;
	CVector V2;
	CVector V3;
};

