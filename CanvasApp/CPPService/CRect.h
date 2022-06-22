#pragma once
#include "CLine.h"
#include "CTransform2.h"
#include "TopLineShape.h"
#include <vector>
using namespace std;

class CRect:public TopLineShape
{
public:
	CRect(CP2 pos,double width,double length);
	~CRect();
public:
	vector<CP2> OutLinePts;
	CTransform2 Transform;
};

